#include "mainwindow1.h"
#include "assignmentdialog.h"
#include "closeticket.h"
#include "customerlist.h"
#include "emaildialog.h"
#include "homewindow.h"
#include "ui_mainwindow1.h"
#include <QDate>
#include <QSqlQuery>
#include <QDebug>

MainWindow1::MainWindow1(const QString &companyName, int ticketNumber, const QString &requester,const QString &affectedUser, const QString &description, const QString &priority, const QString &category, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)

{
    ui->setupUi(this);

    this->ticketNumber = ticketNumber; // Store the ticket number
    ui->companyNameLabel->setText(companyName);
    ui->ticketNumberLabel1->setText(QString::number(ticketNumber));
    ui->CategorycomboBox->setCurrentText(category);
    ui->AffectedUserLineEdit->setText(affectedUser);
    ui->RequesterLineEdit->setText(requester);
    ui->DescriptionLineEdit->setText(description);
    ui->PriorityBox->setCurrentText(priority);



    connect(ui->RefreshupdateButton, &QPushButton::clicked, this, &MainWindow1::RefreshupdateButtonClicked);
    connect(ui->actionCustomer, &QAction::triggered, this, &MainWindow1::on_actionCustomer_triggered);
    connect(ui->actionHome, &QAction::triggered, this, &MainWindow1::on_actionHome_triggered);

    CloseTicket *closeTicketDialog = new CloseTicket(this);
    connect(closeTicketDialog, &CloseTicket::ticketClosed, this, &MainWindow1::updateStatusLabel);


    // Display ticket data from the database
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    qDebug() << "Fetching data for ticketNumber: " << ticketNumber;

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tickets WHERE ticketNumber = :ticketNumber");
    query.bindValue(":ticketNumber", ticketNumber);

    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    if (query.next()) {
        qDebug() << "Data fetched successfully!";
        QString affectedUser = query.value("affectedUser").toString();
        QString requester = query.value("requester").toString();
        QString description = query.value("description").toString();
        QString priority = query.value("priority").toString();
        QString category = query.value("category").toString();

        ui->AffectedUserLineEdit->setText(affectedUser);
        ui->RequesterLineEdit->setText(requester);
        ui->DescriptionLineEdit->setText(description);
        ui->PriorityBox->setCurrentText(priority);
        ui->CategorycomboBox->setCurrentText(category);


        QDate currentDate = QDate::currentDate();
        ui->CreatedDatelabel->setText(currentDate.toString(Qt::ISODate));

        QDate projectedDate = currentDate.addDays(7);
        ui->ProjectedDateLabel->setText(projectedDate.toString(Qt::ISODate));
    }
}

MainWindow1::~MainWindow1()
{
    delete ui;
}



void MainWindow1::updateTicketWithOption(const QString &selectedOption)
{

    qDebug() << "Selected Option: " << selectedOption;
}

void MainWindow1::on_actionHome_triggered()
{
    HomeWindow *homeWindow = new HomeWindow(this);
    homeWindow->show();
}

void MainWindow1::RefreshupdateButtonClicked()
{
    // Get the updated values from the UI
    QString affectedUser = ui->AffectedUserLineEdit->text();
    QString requester = ui->RequesterLineEdit->text();
    QString description = ui->DescriptionLineEdit->text();
    QString priority = ui->PriorityBox->currentText();

    // Update the UI with the new values
    ui->AffectedUserLineEdit->setText(affectedUser);
    ui->RequesterLineEdit->setText(requester);
    ui->DescriptionLineEdit->setText(description);
    ui->PriorityBox->setCurrentText(priority);

    // Update the data in the database
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE Tickets SET affectedUser = :affectedUser, requester = :requester, description = :description, priority = :priority "
                  "WHERE ticketNumber = :ticketNumber");
    query.bindValue(":ticketNumber", ticketNumber);
    query.bindValue(":affectedUser", affectedUser);
    query.bindValue(":requester", requester);
    query.bindValue(":description", description);
    query.bindValue(":priority", priority);

    if (!query.exec()) {
        qDebug() << "Update query error: " << query.lastError().text();
        return;
    }

    qDebug() << "Data updated successfully!";
}

void MainWindow1::on_actionCustomer_triggered()
{

    CustomerList *customerList = new CustomerList(this);
    customerList->show();
}

void MainWindow1::on_EmailButton2_clicked()
{
    EmailDialog *EmailDialog = new class EmailDialog(this);
    EmailDialog->show();
}


void MainWindow1::on_EmailButton1_clicked()
{
    EmailDialog *EmailDialog = new class EmailDialog(this);
    EmailDialog->show();
}


void MainWindow1::on_assignButton_clicked()
{
    AssignmentDialog *AssignmentDialog = new class AssignmentDialog(this);
    connect(AssignmentDialog, &AssignmentDialog::optionSelected, this, &MainWindow1::updateAssignButton);
    AssignmentDialog->show();

}

void MainWindow1::updateAssignButton(const QString &option)
{
    ui->assignButton->setText(option);
}


void MainWindow1::on_assignButton1_clicked()
{
    ui->assignButton1->setText("you");
}


void MainWindow1::on_CloseticketButton_clicked()
{
    CloseTicket *CloseTicket = new class CloseTicket(this);
    CloseTicket->show();
}

void MainWindow1::updateStatusLabel()
{
    ui->closelabel->setText("This ticket has closed");
}
