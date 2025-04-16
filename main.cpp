#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;

    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {

        const QString baseName = "Alexandria_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }

    }

    MainWindow w;
    w.show();

    app.setApplicationDisplayName("Alexandria");
    app.setWindowIcon(QIcon("://Resources/Images/book.png"));
    return app.exec();
}
