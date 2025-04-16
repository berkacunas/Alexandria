#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection(const QString &filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);

    return db.open();
}

#endif // CONNECTION_H
