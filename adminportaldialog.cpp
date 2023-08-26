#include "adminportaldialog.h"
#include "ui_adminportaldialog.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QMainWindow>
#include <QDate>




AdminPortalDialog::AdminPortalDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPortalDialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString databasePath = "C:/QMenuBar/admin_database.sqlite";
    db.setDatabaseName(databasePath);
    if (!db.open())
    {
        qDebug() << "Error opening database: " << db.lastError().text();
        // Handle the error appropriately
    }

    displayExistingAdminData();
    connect(ui->editButton, &QPushButton::clicked, this, &AdminPortalDialog::onEditButtonClicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &AdminPortalDialog::onUpdateButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &AdminPortalDialog::onDeleteButtonClicked);
    connect(ui->updateDataButton, &QPushButton::clicked, this, &AdminPortalDialog::onUpdateDataButtonClicked);

}

AdminPortalDialog::~AdminPortalDialog()
{
    db.close();
    delete ui;
}

void AdminPortalDialog::onEditButtonClicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0) {
        return;
    }

    currentlyEditedAdminId = ui->tableWidget->item(selectedRow, 5)->text().toInt(); //Identify by ID
    QString firstName = ui->tableWidget->item(selectedRow, 0)->text();
    QString lastName = ui->tableWidget->item(selectedRow, 1)->text();
    QString dob = ui->tableWidget->item(selectedRow, 2)->text();
    QString email = ui->tableWidget->item(selectedRow, 3)->text();
    QString password = ui->tableWidget->item(selectedRow, 4)->text();

    ui->firstNameLineEdit->setText(firstName);
    ui->lastNameLineEdit->setText(lastName);
    ui->dobLineEdit->setText(dob);
    ui->emailLineEdit->setText(email);
    ui->passwordLineEdit->setText(password);
}

void AdminPortalDialog::onDeleteButtonClicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0) {
        int adminId = ui->tableWidget->item(selectedRow, 5)->text().toInt(); //Identify by ID

        if (!db.isOpen()) {
            qDebug() << "Database is not open.";
            return;
        }

        if (db.transaction()) {
            QSqlQuery query(db);
            query.prepare("DELETE FROM Admins WHERE id = :admin_id");
            query.bindValue(":admin_id", adminId);

            if (!query.exec()) {
                qDebug() << "Delete query error: " << query.lastError().text();
                db.rollback(); // Rollback the transaction
            } else {
                qDebug() << "Record deleted successfully from database";
                db.commit(); // Commit the transaction
            }

            // Remove the row from the table widget
            ui->tableWidget->removeRow(selectedRow);
        } else {
            qDebug() << "Transaction could not be started.";
        }
    }
}





void AdminPortalDialog::onUpdateButtonClicked()
{
    qDebug() << "Database open:" << db.isOpen();
    QString editedFirstName = ui->firstNameLineEdit->text();
    QString editedLastName = ui->lastNameLineEdit->text();
    QString editedDob = ui->dobLineEdit->text();
    QString editedEmail = ui->emailLineEdit->text();
    QString editedPassword = ui->passwordLineEdit->text();

    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0) {
        int adminId = currentlyEditedAdminId; // Use the stored ID from onEditButtonClicked()

        // Update the corresponding record in the database
        QSqlQuery query(db);
        query.prepare("UPDATE Admins SET first_name = :first_name, last_name = :last_name, dob = :dob, email = :email, password = :password WHERE id = :admin_id");
        query.bindValue(":first_name", editedFirstName);
        query.bindValue(":last_name", editedLastName);
        query.bindValue(":dob", editedDob);
        query.bindValue(":email", editedEmail);
        query.bindValue(":password", editedPassword);
        query.bindValue(":admin_id", adminId);

        if (!query.exec()) {
            qDebug() << "Update query error: " << query.lastError().text();
        } else {
            // Update the table widget on the UI
            ui->tableWidget->setItem(selectedRow, 0, new QTableWidgetItem(editedFirstName));
            ui->tableWidget->setItem(selectedRow, 1, new QTableWidgetItem(editedLastName));
            ui->tableWidget->setItem(selectedRow, 2, new QTableWidgetItem(editedDob));
            ui->tableWidget->setItem(selectedRow, 3, new QTableWidgetItem(editedEmail));
            ui->tableWidget->setItem(selectedRow, 4, new QTableWidgetItem(editedPassword));

            // Clear the input fields after update
            ui->firstNameLineEdit->clear();
            ui->lastNameLineEdit->clear();
            ui->dobLineEdit->clear();
            ui->emailLineEdit->clear();
            ui->passwordLineEdit->clear();

            // Clear the row selection
            ui->tableWidget->clearSelection();

            // Refresh the data in the table widget
            displayExistingAdminData();
        }
    }
}


void AdminPortalDialog::displayExistingAdminData()
{
    if (!db.isOpen())
    {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query("SELECT * FROM Admins", db);
    if (!query.exec())
    {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    // Clear the table widget before populating it
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        int id = query.value("id").toInt(); // Get the ID value
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString dob = query.value("dob").toString();
        QString email = query.value("email").toString();
        QString password = query.value("password").toString();


        ui->tableWidget->insertRow(row);

        // Populate the cells in the row
        QTableWidgetItem *itemFirstName = new QTableWidgetItem(firstName);
        QTableWidgetItem *itemLastName = new QTableWidgetItem(lastName);
        QTableWidgetItem *itemDob = new QTableWidgetItem(dob);
        QTableWidgetItem *itemEmail = new QTableWidgetItem(email);
        QTableWidgetItem *itemPassword = new QTableWidgetItem(password);
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));

        ui->tableWidget->setItem(row, 0, itemFirstName);
        ui->tableWidget->setItem(row, 1, itemLastName);
        ui->tableWidget->setItem(row, 2, itemDob);
        ui->tableWidget->setItem(row, 3, itemEmail);
        ui->tableWidget->setItem(row, 4, itemPassword);
        ui->tableWidget->setItem(row, 5, itemId); //primary key

        ++row;
    }
}

void AdminPortalDialog::on_saveButton_clicked()
{
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString dobString = ui->dobLineEdit->text();
    QString userEmail = ui->emailLineEdit->text();
    QString userPassword = ui->passwordLineEdit->text();

    // Convert dobString to YYYY-MM-DD format
    QDate dobDate = QDate::fromString(dobString, "yyyy/MM/dd");
    QString formattedDob = dobDate.toString(Qt::ISODate);

    if (!db.isOpen())
    {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query(db);
    if (!query.prepare("INSERT INTO Admins (first_name, last_name, dob, email, password) "
                       "VALUES (:first_name, :last_name, :dob, :email, :password)"))
    {
        qDebug() << "Prepare error:" << query.lastError().text();
        return;
    }

    // Bind values to placeholders
    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":dob", formattedDob);
    query.bindValue(":email", userEmail);
    query.bindValue(":password", userPassword);

    qDebug() << "First Name:" << firstName;
    qDebug() << "Last Name:" << lastName;
    qDebug() << "Date of Birth:" << dobString;
    qDebug() << "Email:" << userEmail;
    qDebug() << "Password:" << userPassword;
    qDebug() << "SQL Query: " << query.lastQuery();

    if (!query.exec())
    {
        qDebug() << "Insert query error: " << query.lastError().text();

        return;
    }

    qDebug() << "Admin information saved successfully.";

    displayExistingAdminData();



    QMessageBox::information(this, "Success", "Admin information saved successfully.");
}

void AdminPortalDialog::onUpdateDataButtonClicked()
{
    QString editedFirstName = ui->firstNameLineEdit->text();
    QString editedLastName = ui->lastNameLineEdit->text();
    QString editedDob = ui->dobLineEdit->text();
    QString editedEmail = ui->emailLineEdit->text();
    QString editedPassword = ui->passwordLineEdit->text();

    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0) {
        int adminId = currentlyEditedAdminId; // Use the stored ID from onEditButtonClicked()

        // Update the corresponding record in the database
        QSqlQuery query(db);
        query.prepare("UPDATE Admins SET first_name = :first_name, last_name = :last_name, dob = :dob, email = :email, password = :password WHERE id = :admin_id");
        query.bindValue(":first_name", editedFirstName);
        query.bindValue(":last_name", editedLastName);
        query.bindValue(":dob", editedDob);
        query.bindValue(":email", editedEmail);
        query.bindValue(":password", editedPassword);
        query.bindValue(":admin_id", adminId);

        if (!query.exec()) {
            qDebug() << "Update query error: " << query.lastError().text();
        } else {
            // Update the table widget on the UI
            ui->tableWidget->setItem(selectedRow, 0, new QTableWidgetItem(editedFirstName));
            ui->tableWidget->setItem(selectedRow, 1, new QTableWidgetItem(editedLastName));
            ui->tableWidget->setItem(selectedRow, 2, new QTableWidgetItem(editedDob));
            ui->tableWidget->setItem(selectedRow, 3, new QTableWidgetItem(editedEmail));
            ui->tableWidget->setItem(selectedRow, 4, new QTableWidgetItem(editedPassword));

            // Clear the input fields after update
            ui->firstNameLineEdit->clear();
            ui->lastNameLineEdit->clear();
            ui->dobLineEdit->clear();
            ui->emailLineEdit->clear();
            ui->passwordLineEdit->clear();

            // Clear the row selection
            ui->tableWidget->clearSelection();

            // Refresh the data in the table widget
            displayExistingAdminData();
        }
    }
}
