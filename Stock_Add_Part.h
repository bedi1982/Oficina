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

    bool Clear_Form();
private slots:

    bool Check_Empty_Fields_On_Form();

    void on_txt_Part_Description_textChanged();

    void check_Car_Description_Size();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Stock_Add_Part *ui;
};

#endif // ADDPART_H
