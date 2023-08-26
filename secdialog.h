#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlDatabase>

namespace Ui {
class SecDialog;
}

class SecDialog : public QMainWindow
{
    Q_OBJECT

signals:
    void newTicketCreated(const QString &companyName, int ticketNumber,
                          const QString &requester, const QString &affectedUser,
                          const QString &description,const QString &priority);

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void onCreateTicketButtonClicked();
    void on_actionCustomer_triggered();
    void on_actionHome_triggered();


private:
    Ui::SecDialog *ui;
    int ticketCounter = 0; // Initialize the counter
    int generateTicketNumber();
    QString category;
    QSqlDatabase db;
};

#endif // SECDIALOG_H
