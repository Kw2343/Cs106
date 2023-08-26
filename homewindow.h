#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include <QLabel>

#include "qlabel.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void createNewTicketClicked();

public:

    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

public slots:
    void on_createTicketButton_clicked();
    void on_CreateNewContactButton_clicked();
    void displayExistingTicketsData();
    void on_refreshButton_clicked();
    void openTicketDetails(int row, int column);
    void on_actionCustomer_triggered();



private:
    Ui::HomeWindow *ui;
    QSqlDatabase db;
    QLabel* companyNameLabel;

};

#endif // HOMEWINDOW_H
