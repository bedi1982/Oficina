#include "Config_Set_Hour_Cost.h"
#include "ui_Config_Set_Hour_Cost.h"
#include "QSqlQuery"
#include "QSqlError"
#include "QMessageBox"
#include "QDebug"

Config_Set_Hour_Cost::Config_Set_Hour_Cost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config_Set_Hour_Cost)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);

    //just set current value in the spinbox//
    QSqlQuery Set_Current_Hour_Cost;
    Set_Current_Hour_Cost.prepare("SELECT HourCost from HourCost WHERE HourCost_id = 1");

    if (Set_Current_Hour_Cost.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Set_Current_Hour_Cost.lastError().text() + "class Config_Set_Hour_Cost::on_btn_Salvar_clicked() Set_Current_Hour_Cost.exec()");
    }else{
        while(Set_Current_Hour_Cost.next())
        {
            ui->spin_Hour_Cost->setValue(Set_Current_Hour_Cost.value(0).toDouble());
            Hour_Cost = Set_Current_Hour_Cost.value(0).toDouble();
        }
    }
}

Config_Set_Hour_Cost::~Config_Set_Hour_Cost()
{
    delete ui;
}

double Config_Set_Hour_Cost::getHour_Cost() const
{
    return Hour_Cost;
}

void Config_Set_Hour_Cost::setHour_Cost(double value)
{
    Hour_Cost = value;
}

void Config_Set_Hour_Cost::on_btn_Save_clicked()
{
    qDebug() << Hour_Cost;

    if(Hour_Cost != ui->spin_Hour_Cost->text().toDouble()){
        QSqlQuery Update_Hour_Cost;
        Update_Hour_Cost.prepare("update HourCost set HourCost = :Hours_Cost where HourCost_id = 1");
        Update_Hour_Cost.bindValue(":Hours_Cost", ui->spin_Hour_Cost->text().toDouble());

        if (!(Update_Hour_Cost.exec())){
            QMessageBox::critical(this, tr("Erro!"), Update_Hour_Cost.lastError().text() + "Config_Set_Hour_Cost::on_pushButton_clicked()");
        }else{
            QMessageBox::information(this, tr("Success!"), tr("Hour Cost changed to: $ ") + ui->spin_Hour_Cost->text() + tr("\nAs as reminder, this new hour cost will be used only on new Services."                                                                                                              " Old Services will keep the original set Hour cost.\n"));
                    close();
        }
    }else{
        QMessageBox::information(this, tr("Information"), tr("Value not changed. Nothing was done."));
    }
}
