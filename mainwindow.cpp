#include "mainwindow.h"
#include "adminportaldialog.h"
#include "homewindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "databasemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton_login, &QPushButton::clicked, this, &MainWindow::on_pushButton_login_clicked);
    connect(ui->AdminLoginButton, &QPushButton::clicked, this, &MainWindow::onAdminLoginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_login_clicked()
{
    // Open Admins table
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Admins WHERE email = :email AND password = :password");
    query.bindValue(":email", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Login query error: " << query.lastError().text();
    }

    query.finish();


    if (validateUserLogin(username, password)) {
        hide();
        openHomePage();
    } else {
        QMessageBox::warning(this, "Login", "Username and Password are incorrect, please contact Admin");

    }
    // Close Admins table
    db.close();
}



bool MainWindow::validateUserLogin(const QString &username, const QString &password)
{
    QSqlDatabase db = DatabaseManager::instance().getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM Admins WHERE email = :email AND password = :password");
    query.bindValue(":email", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Login query error: " << query.lastError().text();
        return false;
    }

    return query.next(); // Return true if a row was found
}

HomeWindow *homeWindow = nullptr;

void MainWindow::openHomePage()
{
    if (!homeWindow) {
        homeWindow = new HomeWindow(this);
        connect(homeWindow, &HomeWindow::createNewTicketClicked, this, &MainWindow::openCreateTicketDialog);
    }
    homeWindow->show();
}


void MainWindow::openCreateTicketDialog()
{
    SecDialog *createTicketDialog = new SecDialog(this);
    createTicketDialog->show();
}

void MainWindow::onAdminLoginButtonClicked()
{
    QString adminUsername = "Kelvin_admin";
    QString adminPassword = "12345";

    QString enteredUsername = ui->lineEdit_username->text();
    QString enteredPassword = ui->lineEdit_password->text();

    if (enteredUsername == adminUsername && enteredPassword == adminPassword)
    {

        AdminPortalDialog *adminPortal = new AdminPortalDialog(this);
        adminPortal->show();
    }
    else
    {
        // Admin login failed, show an error message
        QMessageBox::warning(this, "Login Error", "Invalid admin credentials.");
    }
}

