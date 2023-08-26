#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();
    void onAdminLoginButtonClicked();

private:
    Ui::MainWindow *ui;
    bool validateUserLogin(const QString &username, const QString &password);
    void openHomePage();
    void openCreateTicketDialog();
};

#endif // MAINWINDOW_H
