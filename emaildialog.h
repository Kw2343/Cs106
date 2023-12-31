#ifndef EMAILDIALOG_H
#define EMAILDIALOG_H

#include <QDialog>

namespace Ui {
class EmailDialog;
}

class EmailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmailDialog(QWidget *parent = nullptr);
    ~EmailDialog();

private slots:
    void on_sendButton_clicked();

private:
    Ui::EmailDialog *ui;
};

#endif // EMAILDIALOG_H
