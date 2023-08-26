#ifndef ADMINPORTALDIALOG_H
#define ADMINPORTALDIALOG_H

#include <QMainWindow> // Change the base class to QMainWindow
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class AdminPortalDialog;
}

class AdminPortalDialog : public QMainWindow // Change the base class here
{
    Q_OBJECT

public:
    explicit AdminPortalDialog(QWidget *parent = nullptr);
    ~AdminPortalDialog();

private slots:
    void on_saveButton_clicked();
    void displayExistingAdminData();
    void onEditButtonClicked();
    void onUpdateButtonClicked();
    void onDeleteButtonClicked();
    void onUpdateDataButtonClicked();

private:
    Ui::AdminPortalDialog *ui;
    QSqlDatabase db;
    QTableWidget *adminTable;
    int currentlyEditedAdminId = -1;
};

#endif // ADMINPORTALDIALOG_H
