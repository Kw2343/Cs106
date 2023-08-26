#ifndef CLOSETICKET_H
#define CLOSETICKET_H

#include <QDialog>

namespace Ui {
class CloseTicket;
}

class CloseTicket : public QDialog
{
    Q_OBJECT

public:
    explicit CloseTicket(QWidget *parent = nullptr);
    ~CloseTicket();

private slots:
    void CloseButtonClicked();

private:
    Ui::CloseTicket *ui;

signals:
    void ticketClosed(QString status, QString note);
};

#endif // CLOSETICKET_H
