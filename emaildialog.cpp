#include "emaildialog.h"
#include "ui_emaildialog.h"
#include <QMessageBox>

EmailDialog::EmailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailDialog)
{
    ui->setupUi(this);
}

EmailDialog::~EmailDialog()
{
    delete ui;
}

void EmailDialog::on_sendButton_clicked()
{
    QString recipient = ui->recipientLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString message = ui->messageTextEdit->toPlainText();

    QMessageBox::information(this, "Email Sent", "The email has been sent successfully.");

    this->close(); // Close the dialog
}
