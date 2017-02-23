#ifndef EMPLOYEE_ADD_H
#define EMPLOYEE_ADD_H

#include <QDialog>

namespace Ui {
class Employee_Add;
}

class Employee_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Employee_Add(QWidget *parent = 0);
    ~Employee_Add();

private slots:

    void on_btn_Add_Client_accepted();

    void on_btn_Add_Client_rejected();

private:
    Ui::Employee_Add *ui;
    void Set_Emoticon();
    bool Verify_Empty_Fields_on_Form();
    void Clear_Form();
};

#endif // EMPLOYEE_ADD_H
