#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#define PUBLIC
#define PRIVATE

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const QString _dbfile = "/home/valjean/Documents/Databases/Alexandria.db";
    QMessageBox _msgBox;

    int showMessageBox(const QString &title, const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                                 QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

};
#endif // MAINWINDOW_H
