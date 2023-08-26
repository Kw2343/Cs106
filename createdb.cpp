#include <QtSql>

int main() {
    // Initialize the SQLite database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tickets.db"); // This will create or open the "tickets.db" file in your project directory

    if (!db.open()) {
        qDebug() << "Database connection error: " << db.lastError().text();
        return 1;
    }

    // Create a table to store tickets
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS tickets ("
               "ticketNumber INTEGER PRIMARY KEY,"
               "companyName TEXT,"
               "requester TEXT,"
               "affectedUser TEXT,"
               "description TEXT,"
               "priority TEXT)");

    if (!query.isActive()) {
        qDebug() << "Table creation error: " << query.lastError().text();
        return 1;
    }

    // Close the database connection
    db.close();

    return 0;
}
