#include "closeticket.h"
#include "ui_closeticket.h"
#include <QComboBox>

CloseTicket::CloseTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloseTicket)
{
    ui->setupUi(this);
    connect(ui->CloseButton, &QPushButton::clicked, this, &CloseTicket::CloseButtonClicked);

}

CloseTicket::~CloseTicket()
{
    delete ui;
}


void CloseTicket::CloseButtonClicked()
{
    // Get the selected option from the combo box
    QString StatuscomboBox = ui->StatuscomboBox->currentText();
    QString NoteLineEdit = ui-> NoteLineEdit->text();

    emit ticketClosed(StatuscomboBox,NoteLineEdit);

    this->close();
}
