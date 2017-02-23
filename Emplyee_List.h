#ifndef EMPLYEE_LIST_H
#define EMPLYEE_LIST_H

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

private:
    Ui::Employee_List *ui;
};

#endif // EMPLYEE_LIST_H
