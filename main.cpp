#include "mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QApplication>
#include "databasemanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseManager::instance();

    // Load the SQLite driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Set the database name
    db.setDatabaseName("C:/QMenuBar/admin_database.sqlite");

    // Open the database connection
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
        return 1;
    }

    // Create and show the main window
    MainWindow w;
    w.show();

    // Connect to the aboutToQuit signal and close the database connection when the application is about to quit
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&db]() {
        db.close();
    });

    return a.exec();
}
