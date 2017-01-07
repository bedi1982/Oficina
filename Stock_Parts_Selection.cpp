#include "Stock_Parts_Selection.h"
#include "ui_Stock_Parts_Selection.h"

#include "QMessageBox"
#include <QSqlTableModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"


Stock_Parts_Selection::Stock_Parts_Selection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Parts_Selection)
{
    ui->setupUi(this);
    ui->line_NomeDaPeca->setFocus();
    ui->line_NomeDaPeca->setText("*"); //Just so all parts are showed by default//
}

Stock_Parts_Selection::~Stock_Parts_Selection()
{
    delete ui;
}

QString Stock_Parts_Selection::getServiceID() const
{
    return serviceID;
}

void Stock_Parts_Selection::setServiceID(QString serviceid)
{
    serviceID = serviceid;
}

void Stock_Parts_Selection::on_line_NomeDaPeca_textChanged(const QString &userSearchFfilter)
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

void Stock_Parts_Selection::on_tbl_PartsList_doubleClicked(const QModelIndex &DoubleClickedCellValue)
{
    //YES NO DIALOG//
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Confirmação", "Adicionar a peça ao serviço?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        //Bellow 2 lines extract the first column value, which is the partID//
        const QAbstractItemModel * model = DoubleClickedCellValue.model();
        QVariant partId = model->data(model->index(DoubleClickedCellValue.row(), 0, DoubleClickedCellValue.parent()), Qt::DisplayRole);

        //Remove 1 from Stock//
        QSqlQuery removeOnefromStock;
        removeOnefromStock.prepare("UPDATE Part SET Part_Quantity = Part_Quantity - 1 WHERE Part_id = :partId");
        removeOnefromStock.bindValue(":partId", partId.toString());

        //Add to table that maps on which service this part was used//
        QSqlQuery map_Part_to_usedBy_Service_ID;
        map_Part_to_usedBy_Service_ID.prepare("INSERT INTO ServicePartsUsed (Used_On_What_Service_id, Used_Part_ID) VALUES (:Used_On_What_Service_id, :Used_Part_ID)");
        map_Part_to_usedBy_Service_ID.bindValue(":Used_On_What_Service_id", serviceID);
        map_Part_to_usedBy_Service_ID.bindValue(":Used_Part_ID", partId.toString());

        if ((map_Part_to_usedBy_Service_ID.exec() == false) || (removeOnefromStock.exec() == false)){
            QMessageBox::critical(this, "Error!", map_Part_to_usedBy_Service_ID.lastError().text() + " Stock_Parts_Selection::on_tbl_PartsList_doubleClicked(const QModelIndex &DoubleClickedCellValue)");
        }else{
            QMessageBox::information(this, "Sucesso!", "Peça adicionada ao serviço e estoque atualizado.");
            close();
        }
    }
}
