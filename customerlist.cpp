#include "customerlist.h"
#include "qsqlerror.h"
#include "ui_customerlist.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableWidgetItem>
#include <QDebug>

CustomerList::CustomerList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomerList)
{
    ui->setupUi(this);
    displayCustomerData();

    connect(ui->updateButton, &QPushButton::clicked, this, &CustomerList::on_updateButton_clicked);
}

CustomerList::~CustomerList()
{


    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
            db.close();
    }


    delete ui;
}

void CustomerList::displayCustomerData()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query("SELECT * FROM Customer", db);
    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    ui->customerTableWidget->clearContents();
    ui->customerTableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        int id = query.value("id").toInt();
        QString company = query.value("company").toString();
        QString firstName = query.value("firstName").toString();
        QString lastName = query.value("lastName").toString();
        QString email = query.value("email").toString();
        QString mobile = query.value("mobile").toString();
        QString softphone = query.value("softphone").toString();

        ui->customerTableWidget->insertRow(row);
        ui->customerTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        ui->customerTableWidget->setItem(row, 1, new QTableWidgetItem(company));
        ui->customerTableWidget->setItem(row, 2, new QTableWidgetItem(firstName));
        ui->customerTableWidget->setItem(row, 3, new QTableWidgetItem(lastName));
        ui->customerTableWidget->setItem(row, 4, new QTableWidgetItem(email));
        ui->customerTableWidget->setItem(row, 5, new QTableWidgetItem(mobile));
        ui->customerTableWidget->setItem(row, 6, new QTableWidgetItem(softphone));

        ++row;
    }
}

void CustomerList::on_updateButton_clicked()
{
    displayCustomerData();
}

