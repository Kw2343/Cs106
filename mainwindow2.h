#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QLabel> // Include this for QLabel
#include <QLineEdit> // Include this for QLineEdit
#include <QMainWindow>

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
    explicit MainWindow1(int ticketNumber, const QString &companyName, const QString &requester, const QString &affectedUser, const QString &description, const QString &priority, QWidget *parent);

private slots:
    void on_actionHome_triggered();
    void openAssignmentDialog();
    void updateTicketWithOption(const QString &selectedOption);
    void onEmailButton1Clicked();
    void onEmailButton2Clicked();

private:
    Ui::MainWindow1 *ui;
    QString companyName;
    QString requester;
    QString affectedUser;
    QString description;
    QLabel *companyNameLabel;
    QLineEdit *RequesterLineEdit;
    QLineEdit *AffectedUserLineEdit;
    QLineEdit *DescriptionLineEdit;
};

#endif // MAINWINDOW2_H
