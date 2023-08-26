#ifndef ADMINLOGINDIALOG_H
#define ADMINLOGINDIALOG_H

#include <QDialog>

namespace Ui {
class AdminLoginDialog;
}

class AdminLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLoginDialog(QWidget *parent = nullptr);
    ~AdminLoginDialog();

private slots:
    void on_loginButton_clicked();

private:
    Ui::AdminLoginDialog *ui;
};

#endif // ADMINLOGINDIALOG_H
