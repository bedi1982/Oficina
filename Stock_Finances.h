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
    void Load_All();

private slots:

    void on_buttonBox_rejected();

private:
    Ui::Stock_Finances *ui;
    void LoadSettings();
    void SaveSettings();
};

#endif // STOCK_FINANCES_H
