#ifndef STOCK_FINANCES_H
#define STOCK_FINANCES_H

#include <QDialog>

namespace Ui {
class Stock_Finances;
}

class Stock_Finances : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Finances(QWidget *parent = 0);
    ~Stock_Finances();

private:
    Ui::Stock_Finances *ui;
};

#endif // STOCK_FINANCES_H
