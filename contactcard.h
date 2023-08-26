#ifndef CONTACTCARD_H
#define CONTACTCARD_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class ContactCard;
}

class ContactCard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContactCard(QWidget *parent = nullptr);
    ~ContactCard();

private slots:
    void onSaveButtonClicked();

private:
    Ui::ContactCard *ui;
    int generateId();
};

#endif // CONTACTCARD_H
