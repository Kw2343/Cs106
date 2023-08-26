#include "secdialog.h"
#include "customerlist.h"
#include "homewindow.h"
#include "ui_secdialog.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QMainWindow>
#include <QDate>
#include "mainwindow1.h"
#include "databasemanager.h"


SecDialog::SecDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    connect(ui->createTicketButton, &QPushButton::clicked, this, &SecDialog::onCreateTicketButtonClicked);
    connect(ui->actionCustomer, &QAction::triggered, this, &SecDialog::on_actionCustomer_triggered);
    connect(ui->actionHome, &QAction::triggered, this, &SecDialog::on_actionHome_triggered);

    QDate currentDate = QDate::currentDate();
    ui->CreatedDatelabel->setText("Created Date: " + currentDate.toString(Qt::ISODate));

    QDate projectedDate = currentDate.addDays(7);
    ui->ProjectedDateLabel->setText("Projected Date: " + projectedDate.toString(Qt::ISODate));

    db = QSqlDatabase::addDatabase("QSQLITE", "my_connection");
    QString databasePath = "C:/QMenuBar/admin_database.sqlite";
    db.setDatabaseName(databasePath);
    if (!db.open())
    {
        qDebug() << "Error opening database: " << db.lastError().text();
        // Handle the error appropriately
    }
}

SecDialog::~SecDialog()
{
    db.close();
    delete ui;
}




void SecDialog::onCreateTicketButtonClicked() {
    int ticketNumber = generateTicketNumber();

    QString companyName = ui->CompanyLineEdit->text();
    QString requester = ui->RequesterLineEdit->text();
    QString affectedUser = ui->AffectedUserLineEdit->text();
    QString description = ui->DescriptionLineEdit->text();
    QString priority = ui->PriorityBox->currentText();
    QString category = ui->CategorycomboBox->currentText();
    QDate currentDate = QDate::currentDate();
    QDate projectedDate = currentDate.addDays(7);

    // Insert ticket data into the database
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Tickets (ticketNumber, companyName, requester, affectedUser, description, Priority, createdDate, projectedDate, Category) "
                  "VALUES (:ticketNumber, :companyName, :requester, :affectedUser, :description, :priority, :createdDate, :projectedDate, :category)");
    query.bindValue(":ticketNumber", ticketNumber);
    query.bindValue(":companyName", companyName);
    query.bindValue(":requester", requester);
    query.bindValue(":affectedUser", affectedUser);
    query.bindValue(":description", description);
    query.bindValue(":priority", priority);
    query.bindValue(":createdDate", currentDate.toString(Qt::ISODate));
    query.bindValue(":projectedDate", projectedDate.toString(Qt::ISODate));
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "Query: " << query.lastQuery();
        qDebug() << "Bindings: " << query.boundValues();
        qDebug() << "Last error: " << query.lastError().text();

        return;
    }

    QMessageBox::information(this, "Ticket Created", "Ticket created successfully.");

    // Open MainWindow1 after creating the ticket
    MainWindow1 *mainWindow1 = new MainWindow1(companyName, ticketNumber,requester, affectedUser, description, priority, category, this);
    mainWindow1->show();

    this->close();
}


int SecDialog::generateTicketNumber()
{
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return -1; // Indicate an error
    }

    QSqlQuery query(db);
    query.prepare("SELECT MAX(ticketNumber) FROM Tickets");
    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return -1;
    }

    if (query.next()) {
        int maxTicketNumber = query.value(0).toInt();
        return maxTicketNumber + 1; // Return the next available ticket number
    }

    return 1; // Default to 1 if no existing tickets are found
}


void SecDialog::on_actionCustomer_triggered()
{

    CustomerList *customerList = new CustomerList(this);
    customerList->show();
}

void SecDialog::on_actionHome_triggered()
{
    HomeWindow *homeWindow = new HomeWindow(this);
    homeWindow->show();
}
