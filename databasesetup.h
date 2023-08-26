#ifndef DATABASESETUP_H
#define DATABASESETUP_H

#include <QSqlDatabase>

class DatabaseSetup
{
public:
    DatabaseSetup();
    bool createDatabase();
private:
    QSqlDatabase db;
};

#endif // DATABASESETUP_H
