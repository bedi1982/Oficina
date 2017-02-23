#ifndef EMPLOYEE_UPDATE_H
#define EMPLOYEE_UPDATE_H

#include <QDialog>

namespace Ui {
class Employee_Update;
}

class Employee_Update : public QDialog
{
    Q_OBJECT

public:
    explicit Employee_Update(QWidget *parent = 0);
    ~Employee_Update();

    QString employee_id;

    QString getEmployee_id() const;
    void setEmployee_id(const QString &value);

private slots:
    void on_btn_Employee_Update_accepted();

private:
    Ui::Employee_Update *ui;
    void load_Employee_Info_To_TextBoxes();
};

#endif // EMPLOYEE_UPDATE_H
