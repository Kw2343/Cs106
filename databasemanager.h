#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    QSqlQuery createQuery() const;
    QSqlDatabase getDatabase() const;

private:
    DatabaseManager(); // Private constructor for singleton
    ~DatabaseManager();
};
