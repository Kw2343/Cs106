#include "databasemanager.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

DatabaseManager::DatabaseManager()
{
    // Load the SQLite driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Set the database name
    db.setDatabaseName("C:/QMenuBar/helpdesk_database.sqlite");

    // Open the database connection
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
    }
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

QSqlQuery DatabaseManager::createQuery() const
{
    QSqlQuery query(DatabaseManager::instance().getDatabase());
    return query;
}

QSqlDatabase DatabaseManager::getDatabase() const
{
    return QSqlDatabase::database();
}

DatabaseManager::~DatabaseManager()
{
    QSqlDatabase::database().close();
}
