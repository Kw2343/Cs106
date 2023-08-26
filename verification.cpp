#include "verification.h"
#include "ui_verification.h"

Verification::Verification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verification)
{
    ui->setupUi(this);
}

Verification::~Verification()
{
    delete ui;
}
