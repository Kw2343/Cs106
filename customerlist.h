#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include <QMainWindow>

namespace Ui {
class CustomerList;
}

class CustomerList : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerList(QWidget *parent = nullptr);
    ~CustomerList();


private slots:
    void displayCustomerData();
    void on_updateButton_clicked();

private:
    Ui::CustomerList *ui;
};

#endif // CUSTOMERLIST_H
