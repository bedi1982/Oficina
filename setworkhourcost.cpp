#include "setworkhourcost.h"
#include "ui_setworkhourcost.h"
#include "QSqlTableModel"

SetWorkHourCost::SetWorkHourCost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWorkHourCost)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

SetWorkHourCost::~SetWorkHourCost()
{
    delete ui;
}

void SetWorkHourCost::SetNewCost(){

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
