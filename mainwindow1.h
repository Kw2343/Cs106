#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(const QString &companyName, int ticketNumber, const QString &requester,const QString &affectedUser, const QString &description, const QString &priority, const QString &category, QWidget *parent);
    ~MainWindow1();
    QPushButton *RefreshupdateButton;


public slots:
    void updateStatusLabel();

private slots:
    void on_actionHome_triggered();
    void updateTicketWithOption(const QString &selectedOption);
    void RefreshupdateButtonClicked();
    void on_actionCustomer_triggered();
    void on_EmailButton2_clicked();
    void on_EmailButton1_clicked();
    void on_assignButton_clicked();
    void updateAssignButton(const QString &option);
    void on_CloseticketButton_clicked();
    void on_assignButton1_clicked();


private:
    Ui::MainWindow1 *ui;
    QString companyName;
    QString requester;
    QString affectedUser;
    QString priority;
    QString description;
    QString category;
    QLabel *companyNameLabel;
    QLineEdit *RequesterLineEdit;
    QLineEdit *AffectedUserLineEdit;
    QLineEdit *DescriptionLineEdit;
    QComboBox *CategorycomboBox;
    int ticketNumber;



};

#endif // MAINWINDOW1_H
