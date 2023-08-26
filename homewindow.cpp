#include "homewindow.h"
#include "customerlist.h"
#include "ui_homewindow.h"
#include "contactcard.h"
#include "mainwindow1.h"
#include <QtSql>
#include <QLabel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

    QString databasePath = "C:/QMenuBar/admin_database.sqlite";
    qDebug() << "Database path: " << databasePath;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();

    } else {
        qDebug() << "Database opened successfully!";
    }

    displayExistingTicketsData();
    connect(ui->refreshButton, &QPushButton::clicked, this, &HomeWindow::displayExistingTicketsData);
    connect(ui->ticketTableWidget, &QTableWidget::cellClicked, this, &HomeWindow::openTicketDetails);
    connect(ui->actionCustomer, &QAction::triggered, this, &HomeWindow::on_actionCustomer_triggered);
}


HomeWindow::~HomeWindow()
{

   if (db.isOpen()) {
   db.close();
   }

    delete ui;
}

void HomeWindow::displayExistingTicketsData()
{
    if (!db.isOpen())
    {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query("SELECT * FROM Tickets", db);
    if (!query.exec())
    {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    // Clear the table widget before populating it
    ui-> ticketTableWidget->clearContents();
    ui-> ticketTableWidget->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        int ticketNumber = query.value("ticketNumber").toInt();
        QString companyName = query.value("companyName").toString();
        QString priority = query.value("priority").toString();
        QString createdDate = query.value("createdDate").toString();
        QString projectedDate = query.value("projectedDate").toString();
        QString category = query.value("category").toString();
        QString description = query.value("description").toString();

        ui-> ticketTableWidget->insertRow(row);

        // Populate the cells in the row
        QTableWidgetItem *itemTicketNumber = new QTableWidgetItem(QString::number(ticketNumber));
        QTableWidgetItem *itemCompanyName = new QTableWidgetItem(companyName);
        QTableWidgetItem *itemPriority = new QTableWidgetItem(priority);
        QTableWidgetItem *itemCreatedDate = new QTableWidgetItem(createdDate);
        QTableWidgetItem *itemProjectedDate = new QTableWidgetItem(projectedDate);
        QTableWidgetItem *itemCategory = new QTableWidgetItem(category);
        QTableWidgetItem *itemDescription = new QTableWidgetItem(description);

        ui-> ticketTableWidget->setItem(row, 0, itemTicketNumber);
        ui-> ticketTableWidget->setItem(row, 1, itemCompanyName);
        ui-> ticketTableWidget->setItem(row, 2, itemPriority);
        ui-> ticketTableWidget->setItem(row, 3, itemCreatedDate);
        ui-> ticketTableWidget->setItem(row, 4, itemProjectedDate);
        ui-> ticketTableWidget->setItem(row, 5, itemCategory);
        ui-> ticketTableWidget->setItem(row, 6, itemDescription);

        ++row;
    }
}



void HomeWindow::on_createTicketButton_clicked()
{
    emit createNewTicketClicked();
}


void HomeWindow::on_CreateNewContactButton_clicked()
{
    ContactCard *contactCard = new ContactCard(this);
    contactCard->show();
}

void HomeWindow::on_refreshButton_clicked()
{
    qDebug() << "Refreshing data...";
    if (db.isOpen()) {
        qDebug() << "Database is open. Fetching data...";
        displayExistingTicketsData(); // Fetch and display data from the database
    } else {
        qDebug() << "Database is not open.";
    }
}

void HomeWindow::openTicketDetails(int row, int column)
{

    qDebug() << "Cell clicked at row:" << row << "column:" << column;
    qDebug() << "Is database open?" << db.isOpen();
    qDebug() << "Cell clicked at row:" << row << "column:" << column;

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Error reopening database: " << db.lastError().text();
            return;
        }
    }

    if (column == 0)
    {
        QTableWidgetItem *ticketNumberItem = ui->ticketTableWidget->item(row, column);
        if (ticketNumberItem)
        {
            int ticketNumber = ticketNumberItem->text().toInt();

            QSqlQuery ticketQuery(db); // Rename the query object to avoid conflicts
            ticketQuery.prepare("SELECT * FROM Tickets WHERE ticketNumber = :ticketNumber");
            ticketQuery.bindValue(":ticketNumber", ticketNumber);

            if (!ticketQuery.exec()) {
                qDebug() << "Select query error: " << ticketQuery.lastError().text();
                return;
            }

            if (ticketQuery.next()) {
                QString companyName = ticketQuery.value("companyName").toString();
                QString requester = ticketQuery.value("requester").toString();
                QString affectedUser = ticketQuery.value("affectedUser").toString();
                QString description = ticketQuery.value("description").toString();
                QString priority = ticketQuery.value("Priority").toString();
                QString category = ticketQuery.value("category").toString();

                // Open the MainWindow1 with the selected ticket data
                MainWindow1 *mainWindow1 = new MainWindow1(companyName, ticketNumber, requester, affectedUser, description, priority, category, this);
                mainWindow1->show();
            }
        }
    }
}

void HomeWindow::on_actionCustomer_triggered()
{

    CustomerList *customerList = new CustomerList(this);
    customerList->show();
}
