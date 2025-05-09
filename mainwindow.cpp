#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTableView>
#include <QHeaderView>
#include <QFileDialog>

#include <filesystem>
#include <sstream>

#include "globalvars.h"

void ParseCallback(std::vector<std::string> wordList);
void LibibCallback(Libib libib);


PUBLIC MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->verticalLayoutMain->addStretch(1);

    action_NewDatabase = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew), tr("&New"), this);
    action_NewDatabase->setShortcuts(QKeySequence::New);
    action_NewDatabase->setStatusTip(tr("Create a new database"));
    connect(action_NewDatabase, &QAction::triggered, this, &MainWindow::newDatabase);

    action_OpenDatabase = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen), tr("&Open..."), this);
    action_OpenDatabase->setShortcuts(QKeySequence::Open);
    action_OpenDatabase->setStatusTip(tr("Open an existing database"));
    connect(action_OpenDatabase, &QAction::triggered, this, &MainWindow::openDatabase);

    action_DisplayDatabaseDrivers = new QAction(QIcon(), tr("&Display..."), this);
    action_DisplayDatabaseDrivers->setStatusTip(tr("Display database drivers"));
    connect(action_DisplayDatabaseDrivers, &QAction::triggered, this, &MainWindow::displayDatabaseDrivers);

    action_importLibib = new QAction(QIcon(), tr("Import Libib Csv"), this);
    action_importLibib->setStatusTip(tr("Import Libib Csv"));
    connect(action_importLibib, &QAction::triggered, this, &MainWindow::importLibibCsv);

    action_importTsv = new QAction(QIcon(), tr("Import Tsv"), this);
    action_importTsv->setStatusTip(tr("Import Tsv"));
    connect(action_importTsv, &QAction::triggered, this, &MainWindow::importTsv);

    menuBar = QMainWindow::menuBar();

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(action_NewDatabase);
    fileMenu->addAction(action_OpenDatabase);
    fileMenu->addAction(action_DisplayDatabaseDrivers);
    fileMenu->addSeparator();
    fileMenu->addAction(action_importLibib);
    fileMenu->addAction(action_importTsv);

    editMenu = menuBar->addMenu(tr("&Edit"));
    viewMenu = menuBar->addMenu(tr("&View"));
    toolsMenu = menuBar->addMenu(tr("&Tools"));
    windowMenu = menuBar->addMenu(tr("&Window"));
    helpMenu = menuBar->addMenu(tr("&Help"));


    fileToolBar = new QToolBar();
    fileToolBar->addAction(action_NewDatabase);
    fileToolBar->addAction(action_OpenDatabase);
    fileToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, fileToolBar);


    contentsWindow = new QDockWidget(tr("Table of Contents"), this);
    contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

    headingList = new QListWidget(contentsWindow);
    connect(headingList, &QListWidget::itemClicked, this, &MainWindow::openRecord);
    //headingList->viewport()->installEventFilter(this);
    this->setHeadingList();

    contentsWindow->setWidget(headingList);

    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *vMainlayout = new QVBoxLayout(centralWidget);
    QTableView *tableView = new QTableView();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setGridStyle(Qt::SolidLine);
    tableView->setShowGrid(true);
    tableView->setModel(this->createTestModel(tableView));

    vMainlayout->addWidget(tableView);

    this->statusBar()->showMessage(tr("Ready"));

    foo();  // for test purposes.
}

PROTECTED void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MyLineEdit : keyPressEvent , key : " << event->text();
    qDebug() << " ChildLineEdit,keyPressEvent , key : " << event->text();
    qDebug() << "Event accepted : " << event->isAccepted();

    event->ignore();
}

PROTECTED void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    qDebug() << "QCloseEvent : Application closed";
}

PROTECTED bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    /*
    if(target == headingList->viewport()) {
        if(event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            QPoint pos = mouseEvent->pos();
            QListWidgetItem *item = headingList->itemAt(pos);
            if(item)
                qDebug() << "List Widget Item Clicked: " << item->text();

            this->openRecord(target);
            event->ignore();
            return true;
        }
    }
    */
    return QWidget::eventFilter(target, event);
}

CALLBACK void ParseCallback(std::vector<std::string> wordList)
{
    qDebug() << "WordList: " << wordList;
}

CALLBACK void LibibCallback(Libib libib)
{
    try {
        qDebug() << QString::fromStdString(libib.toStr());
    }
    catch (std::exception &r) {
        qDebug() << QString::fromStdString(std::string(r.what()).append(" " + libib.Title()));
    }
}

PUBLIC_SLOT void MainWindow::newDatabase()
{
    if (!std::filesystem::is_directory(DEFAULT_DB_PATH))
        if (!std::filesystem::create_directory(DEFAULT_DB_PATH))
            this->showMessageBox(QMessageBox::Critical, "Error", "Cannot create database file path !", QMessageBox::Ok, QMessageBox::Ok);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Create database..."), DEFAULT_DB_PATH, tr("SqLite File (*.db)"), nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty())
        return;

    if (!std::filesystem::is_regular_file(fileName.toStdString())) {
        int count = createDatabase(CREATESCRIPT_FILE, fileName);

        std::string msg = "Database " + std::filesystem::path(fileName.toStdString()).stem().string() + " with " + std::to_string(count) + " tables created.";
        this->statusBar()->showMessage(tr(msg.c_str()));
    }

    try {
        createConnection(fileName);
    }
    catch (std::exception &r) {
        this->showMessageBox(QMessageBox::Critical, "Error", r.what(), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
}

PUBLIC_SLOT void MainWindow::openDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), DEFAULT_DB_PATH, tr("SqLite File (*.db)"), nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty())
        return;

    try {
        createConnection(fileName);
    }
    catch (std::exception &r) {
        this->showMessageBox(QMessageBox::Critical, "Error", r.what(), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    this->showMessageBox(QMessageBox::Information, "Connected", "Connected to " + fileName, QMessageBox::Ok, QMessageBox::Ok);
}

PUBLIC_SLOT void MainWindow::displayDatabaseDrivers()
{
    std::string sqlDrivers = this->getRegisteredQSqlDrivers();
    this->showMessageBox(QMessageBox::Information, "Registered QSqlDatabases", QString::fromStdString(sqlDrivers), QMessageBox::Ok, QMessageBox::Ok);
}

PUBLIC_SLOT void MainWindow::importLibibCsv()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\berk\\Documents\\Databases\\Libib", tr("CSV file (*.csv)"));
    if (fileName.isEmpty())
        return;

    _libibParser = new LibibParser(fileName.toStdString());
    std::vector<std::vector<std::string>> wordLists = _libibParser->parse(',', ParseCallback);

    LibibCollection libibs;
    for (int i = 0; i < wordLists.size(); ++i) {
        Libib libib = _libibParser->readLine(wordLists[i], LibibCallback);
        if (libib.ItemType() == "book")
            libibs.addItem(libib);

        /*
        QSqlQuery query;
        query.prepare(QString("INSERT INTO Book(id, Name, Pages, PublisherId, LanguageId, ShopId, IsRead, LastReadDate, Price, PurchasedDay, AddDate)) ") +
                      QString("VALUES (:id, :Name, :Pages, :PublisherId, :LanguageId, :ShopId, :IsRead, :LastReadDate, :Price, :PurchasedDay, :AddDate)"));


        query.bindValue(":Name", QString::fromStdString(libib.Title()));
        query.bindValue(":Pages", 1);

        query.bindValue(":PublisherId", 1);
        query.bindValue(":LanguageId", 1);
        query.bindValue(":ShopId", 1);
        query.bindValue(":IsRead", false);
        query.bindValue(":LastReadDate", QString::fromStdString(std::to_string(libib.Completed().tm_wday) + std::to_string(libib.Completed().tm_mon) + std::to_string(libib.Completed().tm_year)));
        query.bindValue(":Price", libib.Price());
        query.bindValue(":PurchasedDay", QString::fromStdString(std::to_string(libib.PublishDate().tm_wday) + std::to_string(libib.PublishDate().tm_mon) + std::to_string(libib.PublishDate().tm_year)));
        query.bindValue(":AddDate", QString::fromStdString(std::to_string(libib.Added().tm_wday) + std::to_string(libib.Added().tm_mon) + std::to_string(libib.Added().tm_year)));

        query.exec();
*/
    }
}

PUBLIC_SLOT void MainWindow::importTsv()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\berk\\Documents\\Databases\\Alexandria\\tsv", tr("TSV file (*.tsv)"));
    if (fileName.isEmpty())
        return;

    _tsvParser = new TsvParser();
    _tsvParser->setTsvFile(fileName.toStdString());

    try {
        _tsvParser->setDbFile("C:\\berk\\Documents\\Databases\\Alexandria\\SQLite\\Alexandria_firstcreatedmanually.db");
    }
    catch (std::exception &r) {
        this->showMessageBox(QMessageBox::Critical, "Database not found !", r.what(), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    std::vector<std::vector<std::string>> wordLists;

    try {
        wordLists = _tsvParser->parse('|', false, ParseCallback);
    }
    catch (std::exception &r) {
        this->showMessageBox(QMessageBox::Critical, "Error", r.what(), QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    qDebug() << wordLists.size();

    std::ostringstream ossHeader;
    std::ostringstream ossValues;
    ossHeader << "INSERT INTO " << _tsvParser->tableName() << "(";
    ossValues << "VALUES(";

    std::vector<std::string> columns = _tsvParser->columns();

    for (int i = 0; i < columns.size(); ++i) {
        ossHeader << columns[i];
        ossValues << ":" << columns[i];
        if (i == columns.size() - 1) {
            ossHeader << ")";
            ossValues << ");";
        }
        else {
            ossHeader << ", ";
            ossValues << ", ";
        }
    }

    std::string queryString = ossHeader.str() + " " + ossValues.str();
    qDebug() << queryString;

    ossHeader.clear();
    ossValues.clear();

    QSqlDatabase db = createConnection(QString("C:\\berk\\Documents\\Databases\\Alexandria\\SQLite\\Alexandria.db"));
    db.transaction();

    QSqlQuery query(db);


    qDebug() << "WordLists size: " << wordLists.size();
    for (int i = 1; i < wordLists.size(); ++i) {
        query.prepare(QString::fromStdString(queryString));

        qDebug() << "Column size: " << columns.size();
        for (int k = 1; k < columns.size(); ++k) {
            qDebug() << "i:" << i << " k: " << k << " Column: " << columns[k] << " Value: " << wordLists[i][k];
            query.bindValue(QString::fromStdString(":" + columns[k]), QString::fromStdString(wordLists[i][k]));
        }

        if (!query.exec()) {
            QString errorMessage = "-- QSqlQuery.exec() failed: " + query.lastError().text();
            qWarning() << errorMessage;
            this->showMessageBox(QMessageBox::Critical, "Query error", errorMessage, QMessageBox::Ok, QMessageBox::Ok);
            return;
        }

        query.clear();
    }

    if(!db.commit())
        db.rollback();
}




PRIVATE void MainWindow::openRecord(QListWidgetItem *item)
{
    qDebug() << item->text();
}

PRIVATE int MainWindow::showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    _msgBox.setIcon(icon);
    _msgBox.setText(text);
    _msgBox.setWindowTitle(title);
    _msgBox.setStandardButtons(buttons);
    _msgBox.setDefaultButton(defaultButton);

    return _msgBox.exec();
}

PRIVATE std::string MainWindow::getRegisteredQSqlDrivers()
{
    std::ostringstream ss;
    QStringList drivers = QSqlDatabaseDrivers();
    int length = drivers.length();

    for (int i = 0; i < length; ++i) {
        ss << drivers[i].toStdString();
        if (i < length - 1)
            ss << " ";
    }
    return ss.str();
}

PRIVATE void MainWindow::setHeadingList()
{
    QMap<QString, QIcon> headingListMap;
    headingListMap.insert("Merhaba", QIcon("://Resources/Images/book.png"));

    QMapIterator<QString, QIcon> iterHeadingMap(headingListMap);
    while (iterHeadingMap.hasNext()) {
        iterHeadingMap.next();
        QListWidgetItem *item = new QListWidgetItem(iterHeadingMap.value(), iterHeadingMap.key());
        headingList->addItem(item);
    }
}

PRIVATE QStandardItemModel *MainWindow::createTestModel(QObject* parent)
{
    const int numRows = 10;
    const int numColumns = 10;

    QStandardItemModel *model = new QStandardItemModel(numRows, numColumns);
    for (int row = 0; row < numRows; ++row) {
        for (int column = 0; column < numColumns; ++column) {
            QString text = QString('A' + QString::number(row) + QString::number(column + 1));
            QStandardItem* item = new QStandardItem(text);
            model->setItem(row, column, item);
        }
    }

    return model;
}

PRIVATE void MainWindow::foo()
{
    // For test purposes.
}


MainWindow::~MainWindow()
{
    delete ui;
}
