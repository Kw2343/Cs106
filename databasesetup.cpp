#include "databasesetup.h"
#include <QSqlQuery>
#include <QDebug>
#include <Qtsql>

DatabaseSetup::DatabaseSetup()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tickets.db"); // Change this to your desired database name

    if (!db.open()) {
        qDebug() << "Database connection error: " << db.lastError().text();
    }
}

bool DatabaseSetup::createDatabase()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS tickets ("
               "ticketNumber INTEGER PRIMARY KEY,"
               "companyName TEXT,"
               "requester TEXT,"
               "affectedUser TEXT,"
               "description TEXT,"
               "priority TEXT),"
               "createdDate TEXT,"
               "projectedDate TEXT)");


    if (!query.isActive()) {
        qDebug() << "Table creation error: " << query.lastError().text();
        return false;
    }


    return true;
}

