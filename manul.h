#ifndef MANUL_H
#define MANUL_H

#include <QDialog>

namespace Ui {
class Manul;
}

class Manul : public QDialog
{
    Q_OBJECT

public:
    explicit Manul(QWidget *parent = 0);
    ~Manul();

private:
    Ui::Manul *ui;
};

#endif // MANUL_H
