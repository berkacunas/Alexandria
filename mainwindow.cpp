#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <filesystem>
#include <sstream>

#include "globalvars.h"
#include "connection.h"

PUBLIC MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->verticalLayoutMain->addStretch(1);

    QObject::connect(ui->action_NewDatabase, SIGNAL(triggered()), this, SLOT(action_NewDatabaseHandler()));
    QObject::connect(ui->action_DisplayDatabaseDrivers, SIGNAL(triggered()), this, SLOT(action_DisplayDatabaseDriversHandler()));

}


PUBLIC_SLOT void MainWindow::action_NewDatabaseHandler()
{
    if (!std::filesystem::is_directory(dbPath.toStdString()))
        if (!std::filesystem::create_directory(dbPath.toStdString()))
            this->showMessageBox(QMessageBox::Critical, "Error", "Cannot create database file path !", QMessageBox::Ok, QMessageBox::Ok);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), dbPath, tr("SqLite File (*.db)"), nullptr, QFileDialog::DontUseNativeDialog);

    if (!std::filesystem::is_regular_file(fileName.toStdString())) {
        int count = createDatabase(fileName);
        this->showMessageBox(QMessageBox::Information, "Database Created", QString::fromStdString((std::to_string(count))) + " tables created.", QMessageBox::Ok);
    }

    if (!createConnection(fileName))
        this->showMessageBox(QMessageBox::Critical, "Error", "Cannot connect to SQLite !", QMessageBox::Ok, QMessageBox::Ok);
}

PUBLIC_SLOT void MainWindow::action_OpenDatabaseHandler()
{

}

PUBLIC_SLOT void MainWindow::action_DisplayDatabaseDriversHandler()
{
    std::string sqlDrivers = this->getRegisteredQSqlDrivers();
    this->showMessageBox(QMessageBox::Information, "Registered QSqlDatabases", QString::fromStdString(sqlDrivers), QMessageBox::Ok, QMessageBox::Ok);
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

PUBLIC void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "MyLineEdit : keyPressEvent , key : " << event->text();

    qDebug() << " ChildLineEdit,keyPressEvent , key : " << event->text();
    qDebug() << "Event accepted : " << event->isAccepted();
    event->ignore();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    qDebug() << "QCloseEvent : Application closed";
}

MainWindow::~MainWindow()
{
    delete ui;
}
