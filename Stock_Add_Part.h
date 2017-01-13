#ifndef STOCK_ADD_PART_H
#define STOCK_ADD_PART_H

#include <QDialog>

namespace Ui {
class Stock_Add_Part;
}

class Stock_Add_Part : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Add_Part(QWidget *parent = 0);
    ~Stock_Add_Part();

private slots:
    void on_btn_Exit_clicked();
    void on_btn_Add_clicked();
    bool Check_Empty_Fields_On_Form();
    void on_txt_Part_Description_textChanged();
    void check_Car_Description_Size();

private:
    Ui::Stock_Add_Part *ui;
};

#endif // ADDPART_H
