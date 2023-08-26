#ifndef SECDIALOG1_H
#define SECDIALOG1_H

#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG1_H
