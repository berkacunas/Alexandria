#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QStandardPaths>

static int createDatabase(const QString &dbname);
static bool createConnection(const QString &filename);
static QStringList QSqlDatabaseDrivers();
static int execSqlScriptFile(QSqlDatabase &db, const QString &filename);

const QString genericDataLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation); //AppDataLocation
const QString dbPath = genericDataLocation + "/Alexandria/";
const QString defaultDbName = dbPath + "Alexandria.db";
const QString createTableScript = dbPath + "Alexandria.CreateTables.sql";

static int createDatabase(const QString &dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    db.open();
    if (!db.isOpen())
        return 0;

    return execSqlScriptFile(db, createTableScript);
}

static bool createConnection(const QString &filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);

    return db.open();
}

static QStringList QSqlDatabaseDrivers()
{
    return QSqlDatabase::drivers();
}

static int execSqlScriptFile(QSqlDatabase &db, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return  0;

    QTextStream ts(&file);
    QString sql = ts.readAll();
    QStringList sqlStatements = sql.split(';', Qt::SkipEmptyParts);

    int successCount = 0;
    foreach(const QString &statement, sqlStatements) {
        if (statement.trimmed() != "") {
            QSqlQuery query(db);
            if (query.exec(statement))
                successCount++;
            else
                qDebug() << "Failed:" << statement << "\nReason:" << query.lastError();
        }
    }

    return successCount;
}

#endif // CONNECTION_H
