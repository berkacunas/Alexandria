#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <filesystem>
#include <sstream>

#include "globalvars.h"
#include "connection.h"

PUBLIC MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    QString genericDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation); //AppDataLocation
    QString dbPath = genericDataLocation.append("/Alexandria/");

    if (!std::filesystem::is_directory(dbPath.toStdString()))
        if (!std::filesystem::create_directory(dbPath.toStdString()))
            this->showMessageBox(QMessageBox::Critical, "Error", "Cannot create database file path !", QMessageBox::Ok, QMessageBox::Ok);

    QString dbFile = dbPath.append("Alexandria.db");

    if (!createConnection(dbFile))
        this->showMessageBox(QMessageBox::Critical, "Error", "Cannot connect to SQLite !", QMessageBox::Ok, QMessageBox::Ok);

    this->showRegisteredQSqlDrivers();

    ui->verticalLayoutMain->addStretch(1);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);
    db.open();

    execSqlScriptFile(db, "./Sql/Alexandria.CreateTables.sql");
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

PRIVATE int MainWindow::showRegisteredQSqlDrivers()
{
    std::ostringstream ss;
    QStringList drivers = QSqlDatabaseDrivers();
    int length = drivers.length();

    for (int i = 0; i < length; ++i) {
        ss << drivers[i].toStdString();
        if (i < length - 1)
             ss << " ";
    }

    std::string s = ss.str();
    return this->showMessageBox(QMessageBox::Information, "Registered QSqlDatabases", QString::fromStdString(s), QMessageBox::Ok, QMessageBox::Ok);
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
