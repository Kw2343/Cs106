#include "mainwindow2.h"
#include "emaildialog.h"
#include "ui_mainwindow21.h"
#include "homewindow.h"
#include "assignmentdialog.h"
#include <QDate>

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    connect(ui->assignButton, &QPushButton::clicked, this, &MainWindow1::openAssignmentDialog);


}

MainWindow1::~MainWindow1()
{
    delete ui;
}

MainWindow1::MainWindow1(int ticketNumber,const QString &companyName,const QString &requester,const QString &affectedUser, const QString &description,const QString &priority, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow1), companyName(companyName)
{
    ui->setupUi(this);

    // Set the ticket number in the label
    ui->ticketNumberLabel1->setText(QString::number(ticketNumber));

    // Set the company name label
    ui->companyNameLabel->setText(companyName);

    // Set the requester text
    ui->RequesterLineEdit->setText(requester);

    // Set the affected user text
    ui->AffectedUserLineEdit->setText(affectedUser);

    // Set the description text
    ui->DescriptionLineEdit->setText(description);

    ui->PriorityBox->setCurrentText(priority);

    // Create and set the company name label
    companyNameLabel = new QLabel(this);
    companyNameLabel->setText(companyName);
    companyNameLabel->show();
    ui->companyNameLabel->setText(companyName);

    // Create and set the requester line edit
    RequesterLineEdit = new QLineEdit(this);
    RequesterLineEdit->setText(requester);
    RequesterLineEdit->setReadOnly(false); // Allow editing
    RequesterLineEdit->show();

    // Create and set the affected user line edit
    AffectedUserLineEdit = new QLineEdit(this);
    AffectedUserLineEdit->setText(affectedUser);
    AffectedUserLineEdit->setReadOnly(false); // Allow editing
    AffectedUserLineEdit->show();

    // Create and set the description line edit
    DescriptionLineEdit = new QLineEdit(this);
    DescriptionLineEdit->setText(description);
    DescriptionLineEdit->setReadOnly(false); // Allow editing
    DescriptionLineEdit->show();

    QDate currentDate = QDate::currentDate();
    ui->CreatedDatelabel->setText(currentDate.toString(Qt::ISODate));

    QDate projectedDate = currentDate.addDays(7);
    ui->ProjectedDateLabel->setText(projectedDate.toString(Qt::ISODate));
}

void MainWindow1::openAssignmentDialog()
{
    AssignmentDialog assignDialog(this);
    connect(&assignDialog, &AssignmentDialog::optionSelected, this, &MainWindow1::updateTicketWithOption);
    assignDialog.exec();
}


void MainWindow1::updateTicketWithOption(const QString &selectedOption)
{
    // Update the ticket with the selected option
    // Example: ui->ticketStatusLabel->setText(selectedOption);
    qDebug() << "Selected Option: " << selectedOption;
}

// Add these slots to MainWindow1
void MainWindow1::onEmailButton1Clicked()
{
    EmailDialog emailDialog(this);
    emailDialog.exec();
}

void MainWindow1::onEmailButton2Clicked()
{
    EmailDialog emailDialog(this);
    emailDialog.exec();
}

void MainWindow1::on_actionHome_triggered()
{
    HomeWindow *homeWindow = new HomeWindow(this);
    homeWindow->show();
}
