#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QString>
#include <QDate>

struct ContactData {
    QString company;
    QString customerName;
    QString email;
    QString mobile;
    QString jobTitle;
    QDate account;

    ContactData() = default;
};

#endif // CONTACTDATA_H

