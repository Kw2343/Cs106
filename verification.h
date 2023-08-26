#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QDialog>

namespace Ui {
class Verification;
}

class Verification : public QDialog
{
    Q_OBJECT

public:
    explicit Verification(QWidget *parent = nullptr);
    ~Verification();

private:
    Ui::Verification *ui;
};

#endif // VERIFICATION_H
