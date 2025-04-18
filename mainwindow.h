#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QMessageBox>
#include <QKeyEvent>
#include <QCloseEvent>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    QMessageBox _msgBox;

    int showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                       QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    std::string getRegisteredQSqlDrivers();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void action_NewDatabaseHandler();
    void action_OpenDatabaseHandler();
    void action_DisplayDatabaseDriversHandler();

};

#endif // MAINWINDOW_H
