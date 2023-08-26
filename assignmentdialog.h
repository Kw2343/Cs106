#ifndef ASSIGNMENTDIALOG_H
#define ASSIGNMENTDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class AssignmentDialog;
}

class AssignmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssignmentDialog(QWidget *parent = nullptr);
    ~AssignmentDialog();

signals:
    void optionSelected(const QString &selectedOption);

private slots:
    void confirmButtonClicked();

private:
    Ui::AssignmentDialog *ui;

};

#endif // ASSIGNMENTDIALOG_H
