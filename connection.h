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

#include <sstream>

static int createDatabase(const QString &createScriptFile, const QString &dbname);
static QSqlDatabase createConnection(const QString &filename);
static QStringList QSqlDatabaseDrivers();
static int execSqlFromScriptFile(QSqlDatabase &db, const QString &filename);
static bool createTable(const std::string &dbname, const std::string &tableName, const std::vector<std::string> &columns, bool dropTableIfExists = false);


static int createDatabase(const QString &createScriptFile, const QString &dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    db.open();
    if (!db.isOpen())
        return 0;

    return execSqlFromScriptFile(db, createScriptFile);
}

static QSqlDatabase createConnection(const QString &filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if (db.open())
        return db;

    throw std::exception("createConnection() failed.");
}

static QStringList QSqlDatabaseDrivers()
{
    return QSqlDatabase::drivers();
}

static int execSqlFromScriptFile(QSqlDatabase &db, const QString &filename)
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

static bool createTable(const std::string &dbname, const std::string &tableName, const std::vector<std::string> &columns, bool dropTableIfExists)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(dbname));
    db.open();
    if (!db.isOpen())
        return false;

    std::ostringstream oss;
    bool hasId = false;

    if (dropTableIfExists)
        oss << "CREATE TABLE ";
    else
        oss << "CREATE TABLE IF NOT EXISTS ";
    oss << tableName << "(";

    for (int i = 0; i < columns.size(); ++i) {

        oss << "\"" << columns[i] << "\"";

        std::string subStr = columns[i].substr(columns[i].size() - 2, 2);

        if (columns[i] == "id") {
            hasId = true;
            oss << " INTEGER NOT NULL UNIQUE";
        }
        else if (columns[i].substr(columns[i].size() - 2, 2) == "Id") // Are last 2 chars "Id" ?
            oss << " INTEGER";
        else if (columns[i].find("Date") != std::string::npos) // is string contain "Date" as a substring ?
            oss << " REAL";
        else
            oss << " TEXT";

        if (i == columns.size() - 1) {
            if (hasId)
                oss << ", PRIMARY KEY(\"id\" AUTOINCREMENT)";
            oss << ");";
        }
        else
            oss << ", ";
    }

    QSqlQuery query;
    std::string queryString = oss.str();

    return query.exec(QString::fromStdString(queryString));
}

static bool checkIfTableExists(const std::string &dbname, const std::string &tableName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(dbname));
    db.open();
    if (!db.isOpen())
        return false;

    QSqlQuery query(db);
    query.prepare(QString("SELECT count(name) FROM sqlite_schema WHERE type='table' AND name=:tableName;"));
    query.bindValue(":tableName", QString::fromStdString(tableName));
    query.exec();
    query.next();

    int count = query.value(0).toInt();

    if (db.isOpen())
        db.close();

    return count > 0;
}

