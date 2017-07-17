#include "Stock_Parts_Selection.h"
#include "Stock_Add_Part.h"
#include "ui_Stock_Parts_Selection.h"

#include "QMessageBox"
#include <QSqlTableModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QSqlDatabase"
#include "QSettings"


Stock_Parts_Selection::Stock_Parts_Selection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Parts_Selection)
{
    ui->setupUi(this);
    LoadSettings();
    ui->line_Part_Name->setFocus();
    ui->line_Part_Name->setText("*"); //Just so all parts are showed by default//
}

Stock_Parts_Selection::~Stock_Parts_Selection()
{
    SaveSettings();
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

void Stock_Parts_Selection::on_line_Part_Name_textChanged(const QString &userSearchFfilter)
{

    QSqlTableModel* model = new QSqlTableModel;

    if(!(userSearchFfilter.isEmpty()))
    {
        model->setTable("Part");
        model->setFilter("Part_Quantity > '0'");

        if(!(userSearchFfilter == "*"))
        {
            model->setFilter(" Part_Name like '%" + userSearchFfilter + "%'");
        }
        model->select();
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Brand"));
        model->setHeaderData(3, Qt::Horizontal, tr("Description"));
        model->setHeaderData(4, Qt::Horizontal, tr("Cost"));
        model->setHeaderData(5, Qt::Horizontal, tr("Sell Price"));
        model->setHeaderData(6, Qt::Horizontal, tr("Quantity Available"));
        model->setHeaderData(7, Qt::Horizontal, tr("Updated At"));
        model->setHeaderData(8, Qt::Horizontal, tr("Created at"));

        ui->tbl_Parts_List->hideColumn(3);
        ui->tbl_Parts_List->setModel(model);
        ui->tbl_Parts_List->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_Parts_List->setModel(model);

    }
}

void Stock_Parts_Selection::on_tbl_Parts_List_doubleClicked(const QModelIndex &DoubleClickedCellValue)
{
    //YES NO DIALOG//
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Question, "Question", "Add Part to Service?", QMessageBox::Yes|QMessageBox::No).exec())
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
            QMessageBox::critical(this, tr("Error!"), map_Part_to_usedBy_Service_ID.lastError().text() + " Stock_Parts_Selection::on_tbl_PartsList_doubleClicked(const QModelIndex &DoubleClickedCellValue)");
        }else{
            QMessageBox::information(this, tr("Success!"), tr("Part Added to the Service and Stock updated."));

            //Reload the parts table//
            on_line_Part_Name_textChanged("*");
            //close();
        }
    }
}

void Stock_Parts_Selection::on_btn_Add_Part_to_Stock_clicked()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.exec();

    //Bellow 2 just to 'retrigguer' the parts list grid after a new part is included//
    ui->line_Part_Name->setText(" ");
    ui->line_Part_Name->setText("*");
}

void Stock_Parts_Selection::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Parts_Selection");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Stock_Parts_Selection::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Parts_Selection");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
