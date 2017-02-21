#ifndef CONFIG_SET_HOUR_COST_H
#define CONFIG_SET_HOUR_COST_H

#include <QDialog>

namespace Ui {
class Config_Set_Hour_Cost;
}

class Config_Set_Hour_Cost : public QDialog
{
    Q_OBJECT

public:
    explicit Config_Set_Hour_Cost(QWidget *parent = 0);
    ~Config_Set_Hour_Cost();
    double Hour_Cost;

    double getHour_Cost() const;
    void setHour_Cost(double value);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Config_Set_Hour_Cost *ui;
};

#endif // SETWORKHOURCOST_H
