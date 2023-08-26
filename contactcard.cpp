#include "contactcard.h"
#include "qsqlerror.h"
#include "ui_contactcard.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDateTime>

ContactCard::ContactCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContactCard)
{
    ui->setupUi(this);
    connect(ui->SaveButtonC, &QPushButton::clicked, this, &ContactCard::onSaveButtonClicked);
}

ContactCard::~ContactCard()
{
    delete ui;
}

int ContactCard::generateId()
{
    static int lastGeneratedId = 0;
    lastGeneratedId++;
    return lastGeneratedId;
}

void ContactCard::onSaveButtonClicked()
{
    QString company = ui->CompanylineEdit->text();
    QString firstName = ui->FirstNamelineEdit->text();
    QString lastName = ui->LastNamelineEdit->text();
    QString email = ui->EmaillineEdit->text();
    QString mobile = ui->MobilelineEdit->text();
    QString softphone = ui->PhonelineEdit->text();


    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query(db);


    int id = generateId();

    query.prepare("INSERT INTO Customer (id, company, firstName, lastName, email, mobile, softphone ) "
                  "VALUES (:id, :company, :firstName, :lastName, :email, :mobile, :softphone )");

    query.bindValue(":id", id);
    query.bindValue(":company", company);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":email", email);
    query.bindValue(":mobile", mobile);
    query.bindValue(":softphone", softphone);



    if (!query.exec()) {
        qDebug() << "Insert query error: " << query.lastError().text();
        return;
    }

    db.commit();

    QMessageBox::information(this, "Contact Saved", "Contact saved successfully.");

    this->close();

}
