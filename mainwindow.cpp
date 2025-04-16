#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

#include "connection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    if (!createConnection(_dbfile)) {
        this->showMessageBox("", "Cannot connect to SQLite !", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
}

int MainWindow::showMessageBox(const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    _msgBox.setText(text);
    _msgBox.setInformativeText(title);
    _msgBox.setStandardButtons(buttons);
    _msgBox.setDefaultButton(defaultButton);

    return _msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
