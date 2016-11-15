#include "partsselectionfromlist.h"
#include "ui_partsselectionfromlist.h"

#include "QMessageBox"
#include <QSqlTableModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"


partsSelectionFromList::partsSelectionFromList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::partsSelectionFromList)
{
    ui->setupUi(this);
    ui->line_NomeDaPeca->setFocus();
    ui->line_NomeDaPeca->setText("*"); //Just so all parts are showed by default//
}

partsSelectionFromList::~partsSelectionFromList()
{
    delete ui;
}

QString partsSelectionFromList::getServiceID() const
{
    return serviceID;
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
        model->setFilter("Part_Quantity > '0' ");
        if(!(userSearchFfilter == "*"))
        {
            model->setFilter(" Part_Name like '%" + userSearchFfilter + "%'");
        }
        model->select();

        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        model->setHeaderData(2, Qt::Horizontal, tr("Descrição"));
        model->setHeaderData(3, Qt::Horizontal, tr("Custo"));
        model->setHeaderData(4, Qt::Horizontal, tr("Quantidade"));
        model->setHeaderData(5, Qt::Horizontal, tr("Atualiada em"));
        model->setHeaderData(6, Qt::Horizontal, tr("Criada em"));

        ui->tbl_PartsList->hideColumn(2);
        ui->tbl_PartsList->setModel(model);
        ui->tbl_PartsList->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_PartsList->setModel(model);
    }
}

void partsSelectionFromList::on_tbl_PartsList_doubleClicked(const QModelIndex &DoubleClickedCellValue)
{
    //YES NO DIALOG//
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Confirmação", "Adicionar a peça ao serviço?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        //This extracts the first column value, which is the ServiceID//
        const QAbstractItemModel * model = DoubleClickedCellValue.model();
        QVariant partId = model->data(model->index(DoubleClickedCellValue.row(), 0, DoubleClickedCellValue.parent()), Qt::DisplayRole);

        QSqlQuery query;
        query.prepare("INSERT INTO ServicePartsUsed (Used_On_What_Service_id, Used_Part_ID) VALUES (:Used_On_What_Service_id, :Used_Part_ID)");
        query.bindValue(":Used_On_What_Service_id", serviceID);
        query.bindValue(":Used_Part_ID", partId.toString());

        QSqlQuery removeOnefromStock;
        removeOnefromStock.prepare("UPDATE Part SET Part_Quantity = Part_Quantity - 1 WHERE Part_id = :partId");
        removeOnefromStock.bindValue(":partId", partId.toString());

        if ((query.exec() == false) || (removeOnefromStock.exec() == false)){
            QMessageBox::critical(this, "Erro!", query.lastError().text() + " class partsSelectionFromList.cpp on_tbl_PartsList_doubleClicked()");
        }else{
            QMessageBox::information(this, "Sucesso!", "Peça adicionada ao serviço e estoque atualizado.");
            close();
        }
    }
}
