#include "Config_Set_Hour_Cost.h"
#include "ui_Config_Set_Hour_Cost.h"

#include "qsqlquery.h"
#include "qsqltablemodel.h"
#include "qsqlerror.h"
#include "qdebug.h"

#include "QMessageBox"

Config_Set_Hour_Cost::Config_Set_Hour_Cost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config_Set_Hour_Cost)
{
    ui->setupUi(this);

    //Set current hour cost value in the spinbox//
    Load_Current_Hour_Cost();

    //Load the history os values on the SQL table//
    Load_History_HourCost();
}

Config_Set_Hour_Cost::~Config_Set_Hour_Cost()
{
    delete ui;
}

void Config_Set_Hour_Cost::Load_Current_Hour_Cost()
{
    QSqlQuery Set_Current_Hour_Cost;
    Set_Current_Hour_Cost.prepare("SELECT HourCost FROM HourCost ORDER BY HourCost_id DESC LIMIT 1;");

    if (Set_Current_Hour_Cost.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Set_Current_Hour_Cost.lastError().text() + "class Config_Set_Hour_Cost::Config_Set_Hour_Cost(QWidget *parent)");
    }else{
        while(Set_Current_Hour_Cost.next())
        {
            ui->double_Spin_Hour_Cost->setValue(Set_Current_Hour_Cost.value(0).toDouble());
            setHour_Cost(Set_Current_Hour_Cost.value(0).toDouble());
        }
    }
}

void Config_Set_Hour_Cost::Load_History_HourCost(){
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("HourCost");

    model->select();
    model->removeColumn(0);

    model->setHeaderData(0, Qt::Horizontal, tr("Hour Cost"));
    model->setHeaderData(1, Qt::Horizontal, tr("Created"));

    ui->table_Hour_Cost_History->setModel(model);
    ui->table_Hour_Cost_History->sortByColumn(1, Qt::DescendingOrder);
}

void Config_Set_Hour_Cost::on_buttonBox_accepted()
{
    if(getHour_Cost() != ui->double_Spin_Hour_Cost->value()){
        QSqlQuery Update_Hour_Cost;

        Update_Hour_Cost.prepare("INSERT INTO HourCost (HourCost) VALUES (:Hour_Cost)");
        Update_Hour_Cost.bindValue(":Hour_Cost", ui->double_Spin_Hour_Cost->value());

        if (!(Update_Hour_Cost.exec())){
            QMessageBox::critical(this, tr("Erro!"), Update_Hour_Cost.lastError().text() + "Config_Set_Hour_Cost::on_buttonBox_accepted()");
        }else{
            QMessageBox::information(this, tr("Success!"), tr("Hour Cost changed to: $ ") + ui->double_Spin_Hour_Cost->text() +
                                     tr("\nAs as reminder, this new hour cost will be used only on new Services."
                                        " Old Services will keep the original set Hour cost.\n"));
            close();
        }
    }else{
        QMessageBox::information(this, tr("Information"), tr("Value not changed. Nothing was done."));
    }
}

void Config_Set_Hour_Cost::on_buttonBox_rejected()
{
    close();
}

double Config_Set_Hour_Cost::getHour_Cost() const
{
    return Hour_Cost;
}

void Config_Set_Hour_Cost::setHour_Cost(double value)
{
    Hour_Cost = value;
}
