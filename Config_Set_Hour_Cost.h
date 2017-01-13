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

private slots:
    void on_btn_Save_clicked();

private:
    Ui::Config_Set_Hour_Cost *ui;
};

#endif // SETWORKHOURCOST_H
