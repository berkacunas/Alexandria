#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

#include <filesystem>
#include <sstream>

#include "globalvars.h"
#include "connection.h"
#include "LibibCollection.h"

void libib_parse_callback(std::vector<std::string> wordList);


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


    menuBar = QMainWindow::menuBar();

    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(action_NewDatabase);
    fileMenu->addAction(action_OpenDatabase);
    fileMenu->addAction(action_DisplayDatabaseDrivers);
    fileMenu->addSeparator();
    fileMenu->addAction(action_importLibib);

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
    contentsWindow->setWidget(headingList);

    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    foo();  // for test purposes.
}

PUBLIC void MainWindow::keyPressEvent(QKeyEvent *event)
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

CALLBACK void libib_parse_callback(std::vector<std::string> wordList)
{
    LibibCollection libibCollection;
    Libib libib = libibCollection.parseLine(wordList);
    libibCollection.addItem(libib);

    // qDebug() << QString::fromStdString(std::to_string(wordList.size()));
}

PUBLIC_SLOT void MainWindow::newDatabase()
{
    if (!std::filesystem::is_directory(dbPath.toStdString()))
        if (!std::filesystem::create_directory(dbPath.toStdString()))
            this->showMessageBox(QMessageBox::Critical, "Error", "Cannot create database file path !", QMessageBox::Ok, QMessageBox::Ok);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Create database..."), dbPath, tr("SqLite File (*.db)"), nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty())
        return;

    if (!std::filesystem::is_regular_file(fileName.toStdString())) {
        int count = createDatabase(fileName);
        this->showMessageBox(QMessageBox::Information, "Database Created", QString::fromStdString((std::to_string(count))) + " tables created.", QMessageBox::Ok);
    }

    if (!createConnection(fileName))
        this->showMessageBox(QMessageBox::Critical, "Error", "Cannot connect to SQLite !", QMessageBox::Ok, QMessageBox::Ok);
}

PUBLIC_SLOT void MainWindow::openDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dbPath, tr("SqLite File (*.db)"), nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.isEmpty())
        return;

    if (!createConnection(fileName)) {
        this->showMessageBox(QMessageBox::Critical, "Error", "Cannot connect to SQLite !", QMessageBox::Ok, QMessageBox::Ok);
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
    _libibParser->parse(',', libib_parse_callback);
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

PRIVATE void MainWindow::foo()
{
    // For test purposes.
}


MainWindow::~MainWindow()
{
    delete ui;
}
