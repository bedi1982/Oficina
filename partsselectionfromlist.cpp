#include "partsselectionfromlist.h"
#include "ui_partsselectionfromlist.h"

#include "QMessageBox"
#include <QSqlTableModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"

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


void partsSelectionFromList::on_tbl_PartsList_doubleClicked(const QModelIndex &DoubleClickedCellValue)
{
    //This extracts the first column value, which is the ServiceID//
    const QAbstractItemModel * model = DoubleClickedCellValue.model();
    QVariant partId = model->data(model->index(DoubleClickedCellValue.row(), 0, DoubleClickedCellValue.parent()), Qt::DisplayRole);

    QSqlQuery query;
    query.prepare("insert into ServicePartsUsed (Used_On_Service_id, Part_id) values (:Used_On_Service_id, :Part_id)");
    query.bindValue(":Used_On_Service_id", serviceID);
    query.bindValue(":Part_id", partId.toString());

    if (query.exec() == false){
        QMessageBox::critical(this, "Erro!", query.lastError().text() + " class partsSelectionFromList.cpp49");
}else{
        QMessageBox::information(this, "Sucesso!", "Peça adicionada ao serviço");
        close();
    }
}

