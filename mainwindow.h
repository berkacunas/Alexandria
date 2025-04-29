#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <QStandardPaths>
#include <QMessageBox>
#include <QKeyEvent>
#include <QCloseEvent>

#include <QStandardItemModel>

#include "Libib.h"
#include "libibparser.h"
#include "libibcollection.h"

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

    LibibParser *_libibParser;
    LibibCollection *libibCollection;

    void foo(); // Test Func
    void setHeadingList();


    QStandardItemModel* createTestModel(QObject* parent);

    QAction *action_NewDatabase;
    QAction *action_OpenDatabase;
    QAction *action_DisplayDatabaseDrivers;
    QAction *action_importLibib;
    QAction *action_openRecord;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;

    QDockWidget *contentsWindow;
    QListWidget *headingList;

    int showMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                       QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

    std::string getRegisteredQSqlDrivers();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *target, QEvent *event);

public slots:
    void newDatabase();
    void openDatabase();
    void displayDatabaseDrivers();
    void importLibibCsv();
    void openRecord(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
