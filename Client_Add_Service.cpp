#include "Client_Add_Service.h"
#include "ui_Client_Add_service.h"
#include "Stock_Parts_Selection.h"
#include "Service_Update_Description.h"
#include "Main_Window.h"
#include "QMessageBox"

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"

Client_Add_Service::Client_Add_Service(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add_Service)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->txt_Servicedescription->setReadOnly(true);
    ui->line_ServiceShortDescription->setReadOnly(true);
}

Client_Add_Service::~Client_Add_Service()
{
    delete ui;
}


QString Client_Add_Service::getServiceID() const
{
    return ServiceID;
}

void Client_Add_Service::setServiceID(const QString &value)
{
    ServiceID = value;
}

QString Client_Add_Service::getCarID() const
{
    return CarID;
}

void Client_Add_Service::setCarID(const QString &value)
{
    CarID = value;
}

QString Client_Add_Service::getClientid() const
{
    return clientid;
}

void Client_Add_Service::setClientid(const QString &value)
{
    clientid = value;
}

void Client_Add_Service::on_btn_Exit_clicked()
{
    close();
}

void Client_Add_Service::Add_Service_Description_Text(){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Service_Description, Service_Short_Description from Service where Service_id = " + ServiceID);

    ui->line_ServiceShortDescription->setText(model->data(model->index(0, 1)).toString());
    ui->txt_Servicedescription->setText(model->data(model->index(0, 0)).toString());
}

void Client_Add_Service::Load_Parts_And_Service_Costs_Grid(){

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT ServicePartsUsed_id AS ServiçoUsedID, "
                    "Part_id as 'PeçaID', "
                    "Part_Quantity AS 'Estoque', "
                    "Part_Name AS 'Nome', "
                    "Part_Cost AS 'Custo' "
                    "FROM Part p JOIN ServicePartsUsed pu "
                    "ON pu.Used_Part_ID = p.Part_id "
                    "AND pu.Used_On_What_Service_id = " + ServiceID);

    if(model->query().isSelect()){
        ui->tbl_Parts_Used_In_Service->setModel(model);
        ui->tbl_Parts_Used_In_Service->hideColumn(0);
        ui->tbl_Parts_Used_In_Service->hideColumn(1);
        ui->tbl_Parts_Used_In_Service->hideColumn(2);
        ui->tbl_Parts_Used_In_Service->resizeColumnsToContents();

        //Sum the Parts Used Value and add to doublespin//
        double PartsCost = 0;
        const int column = 4; //"Part_Cost column"//
        for (int row = 0; row < model->rowCount(); ++row) {
            PartsCost += model->data(model->index(row, column)).toDouble();
        }

        QSqlQuery SetServicePartsCost;
        SetServicePartsCost.prepare("update Service set Service_Parts_Cost = :PartsCost where Service_id = " + ServiceID);
        SetServicePartsCost.bindValue(":PartsCost", PartsCost);

        if (SetServicePartsCost.exec() == false){
            QMessageBox::critical(this, tr("Erro!"), SetServicePartsCost.lastError().text() + " class Client_Add_Service::LoadPartsAndServiceCostsGrid() ");
        }
    }
    Add_Service_Description_Text();
    Sum_Costs();
}

void Client_Add_Service::Sum_Costs()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Service_Hours_Duration, Service_Parts_Cost, Service_Hour_Cost, Service_Paid from Service where Service_id = " + ServiceID);

    double Service_Hours_Duration = model->data(model->index(0, 0)).toDouble(); //query result line 0 column 0
    double Service_Parts_Cost = model->data(model->index(0, 1)).toDouble(); //query result line 0 column 1
    double Service_Hour_Cost = model->data(model->index(0, 2)).toDouble(); //query result line 0 column 2

    ui->Spin_Hand_Work_Hours->setValue(Service_Hours_Duration);
    ui->Spin_PartsCost->setValue(Service_Parts_Cost);
    ui->Spin_TotalserviceCost->setValue((Service_Hours_Duration * Service_Hour_Cost) + Service_Parts_Cost);
    ui->Spin_ServiceRegistereHandWorkHours->setValue(Service_Hour_Cost);

    //Service Paid CheckMark 0 for not Paid 1 for Paid
    bool Service_Paid = model->data(model->index(0, 3)).toBool(); //query result line 0 column 3

    if(Service_Paid){
        ui->check_Paid->setChecked(true);
    }else{
        ui->check_Paid->setChecked(false);
    }

}

void Client_Add_Service::on_btn_Add_Parts_Used_In_The_Service_clicked()
{
    Stock_Parts_Selection stock_Parts_Selection;
    stock_Parts_Selection.setServiceID(ServiceID);
    stock_Parts_Selection.setModal(true);
    stock_Parts_Selection.exec();

    Load_Parts_And_Service_Costs_Grid();
}

void Client_Add_Service::on_btn_Save_Hours_Worked_clicked()
{
    QSqlQuery Update_Hours_Worked;
    Update_Hours_Worked.prepare("update Service set Service_Hours_Duration = :Service_Hours_Duration where Service_id = " + ServiceID);

    Update_Hours_Worked.bindValue(":Service_Hours_Duration", ui->Spin_Hand_Work_Hours->text().toDouble());

    if (!(Update_Hours_Worked.exec())){
        QMessageBox::critical(this, tr("Erro!"), Update_Hours_Worked.lastError().text() + "class Client_Add_Service::on_btn_save_hoursWorked_clicked()");
    }else{
        QMessageBox::information(this, tr("Sucesso!"), tr("Horas trabalhadas atualizadas.\n"
                                                   "Custo do Serviço recalculadas no sistema...."));
        Sum_Costs();
    }
}

void Client_Add_Service::on_tbl_Parts_Used_In_Service_doubleClicked(const QModelIndex &index)
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, tr("Confirmação!"), tr("Você deseja realmente remover essa peça desse serviço?"), QMessageBox::Yes|QMessageBox::No).exec())
    {
        //Bellow 2 list will retrieve the column 0 value, which is the ServicePartsUsed_id //
        const QAbstractItemModel * model = index.model();
        QVariant ServicePart_ID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);

        //qDebug() << "ServicePartsUsed_id" << ServicePart_ID;
        QSqlQuery removePartsFromService;
        removePartsFromService.prepare("DELETE FROM ServicePartsUsed WHERE ServicePartsUsed_id = " + ServicePart_ID.toString());
        //removePartsFromService.bindValue(":ServicePartsUsed_id", ServicePart_ID.toString());
        removePartsFromService.exec();

        //RETURN PART TO STOCK//
        //Bellow 2 list will retrieve the column 0 value, which is the ServicePartsUsed_id //
        const QAbstractItemModel * model2 = index.model();
        QVariant partID = model2->data(model2->index(index.row(), 1, index.parent()), Qt::DisplayRole);
        //qDebug() << "PartID" << partID;

        QSqlQuery returnPartToStock;
        returnPartToStock.prepare("UPDATE Part SET Part_Quantity = (Part_Quantity + 1) WHERE Part_id = :partID");
        returnPartToStock.bindValue(":partID", partID.toString());

        if(returnPartToStock.exec() == false){
            QMessageBox::critical(this, tr("Erro!"), returnPartToStock.lastError().text() + "class addservice.cpp  on_btn_save_hoursWorked_clicked()");
        }
        Load_Parts_And_Service_Costs_Grid();
    }
}

void Client_Add_Service::on_check_Paid_clicked()
{
    if(ui->check_Paid->isChecked()){
        QSqlQuery query;
        query.prepare("UPDATE Service set Service_Paid = 1 where Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class addservice.cpp  on_check_Pago_clicked ");
        }else{
            QMessageBox::information(this, tr("Pago?!"), tr("Serviço alterado para:\n Pago"));
        }
    }else{
        QSqlQuery query;
        query.prepare("UPDATE Service set Service_Paid = 0 where Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class addservice.cpp on_check_Pago_clicked(not checked) ");
        }else{
            QMessageBox::information(this, tr("Pago?"), tr("Serviço alterado para:\n Não Pago"));
        }
    }
}

void Client_Add_Service::on_btn_Update_Service_Description_clicked()
{
    Service_Update_Description service_Update_Description;
    service_Update_Description.setServiceID(ServiceID);
    service_Update_Description.SetDescription();
    service_Update_Description.setModal(true);
    service_Update_Description.exec();
    Add_Service_Description_Text();
}