#include "assignmentdialog.h"
#include "ui_assignmentdialog.h"
#include <QDebug> // Include this for qDebug()

AssignmentDialog::AssignmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssignmentDialog)
{
    ui->setupUi(this);

    // Populate the combo box with options
    ui->comboBox->addItem("Software team");
    ui->comboBox->addItem("Take Ownership");
    ui->comboBox->addItem("Hardware team");

    connect(ui->confirmButton, &QPushButton::clicked, this, &AssignmentDialog::confirmButtonClicked);
}

AssignmentDialog::~AssignmentDialog()
{
    delete ui;
}

void AssignmentDialog::confirmButtonClicked()
{
    // Get the selected option from the combo box
    QString selectedOption = ui->comboBox->currentText();

    // Emit the signal with the selected option
    emit optionSelected(selectedOption);

    this->close();
}
