#include "partsselectionfromlist.h"
#include "ui_partsselectionfromlist.h"

#include "QMessageBox"
#include <QSqlTableModel>
#include "QSqlQuery"
//#include "QDebug"
//#include "QSqlError"

QString serviceID;

partsSelectionFromList::partsSelectionFromList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::partsSelectionFromList)
{
    ui->setupUi(this);
}

partsSelectionFromList::~partsSelectionFromList()
{
    delete ui;
}

void partsSelectionFromList::setServiceID(QString serviceid)
{
    serviceID = serviceid;
}

void partsSelectionFromList::on_line_NomeDaPeca_textChanged(const QString &userSearchFfilter)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(userSearchFfilter.isEmpty()))
    {
        model->setTable("Part");
        if(!(userSearchFfilter == "*"))
        {
            model->setFilter(" Part_Name like '%" + userSearchFfilter + "%'");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        ui->tbl_PartsList->setModel(model);
    }else{
        model->clear();
        ui->tbl_PartsList->setModel(model);
    }
}
