#ifndef EMPLOYEE_LIST_H
#define EMPLOYEE_LIST_H

#include <QDialog>

namespace Ui {
class Employee_List;
}

class Employee_List : public QDialog
{
    Q_OBJECT

public:
    explicit Employee_List(QWidget *parent = 0);
    ~Employee_List();

private slots:
    void on_line_ID_or_CPG_or_Name_textChanged(const QString &arg1);

    void on_btn_Add_clicked();

    void on_Clear_Button_clicked();

private:
    Ui::Employee_List *ui;
};

#endif // EMPLOYEE_LIST_H
