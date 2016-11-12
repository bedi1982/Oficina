#ifndef SETWORKHOURCOST_H
#define SETWORKHOURCOST_H

#include <QDialog>

namespace Ui {
class SetWorkHourCost;
}

class SetWorkHourCost : public QDialog
{
    Q_OBJECT

public:
    explicit SetWorkHourCost(QWidget *parent = 0);
    ~SetWorkHourCost();
    void SetNewCost();

private:
    Ui::SetWorkHourCost *ui;
};

#endif // SETWORKHOURCOST_H
