#include "Config_Set_Hour_Cost.h"
#include "ui_Config_Set_Hour_Cost.h"
#include "QSqlTableModel"

Config_Set_Hour_Cost::Config_Set_Hour_Cost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config_Set_Hour_Cost)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

Config_Set_Hour_Cost::~Config_Set_Hour_Cost()
{
    delete ui;
}

void Config_Set_Hour_Cost::SetNewCost(){

    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("HourCost");

    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setHeaderData(1, Qt::Horizontal, tr("Insira o Custo por Hora"));
    model->setHeaderData(2, Qt::Horizontal, tr("Ultima atualização"));

    ui->tbl_SetHourCost->setModel(model);
    ui->tbl_SetHourCost->resizeColumnsToContents();
        ui->tbl_SetHourCost->hideColumn(0);
}
