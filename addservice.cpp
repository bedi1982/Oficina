#include "addservice.h"
#include "ui_addservice.h"
#include "partsselectionfromlist.h"
#include "updatedservicedescription.h"
#include "mainwindow.h"
#include "QMessageBox"

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"

addservice::addservice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addservice)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

addservice::~addservice()
{
    delete ui;
}


QString addservice::getServiceID() const
{
    return ServiceID;
}

void addservice::setServiceID(const QString &value)
{
    ServiceID = value;
}

QString addservice::getCarID() const
{
    return CarID;
}

void addservice::setCarID(const QString &value)
{
    CarID = value;
}

QString addservice::getClientid() const
{
    return clientid;
}

void addservice::setClientid(const QString &value)
{
    clientid = value;
}

void addservice::on_btn_Sair_clicked()
{
    close();
}

void addservice::addserviceDescriptionText(){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Service_Description, Service_Short_Description from Service where Service_id = " + ServiceID);

    ui->line_ServiceShortDescription->setText(model->data(model->index(0, 0)).toString());
    ui->txt_Servicedescription->setText(model->data(model->index(0, 1)).toString());
}

void addservice::LoadPartsAndServiceCostsGrid(){

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
        ui->tbl_PartsUsedInService->setModel(model);
        ui->tbl_PartsUsedInService->hideColumn(0);
        ui->tbl_PartsUsedInService->hideColumn(1);
        ui->tbl_PartsUsedInService->hideColumn(2);
        ui->tbl_PartsUsedInService->resizeColumnsToContents();

        //Sum the Parts Used Value and add to doublespin//
        double PartsCost = 0;
        const int column = 4; //"Part_Cost AS 'Custo' "
        for (int row = 0; row < model->rowCount(); ++row) {
            PartsCost += model->data(model->index(row, column)).toDouble();
        }

        QSqlQuery SetServicePartsCost;
        SetServicePartsCost.prepare("update Service set Service_Parts_Cost = :PartsCost where Service_id = :ServiceID");
        SetServicePartsCost.bindValue(":PartsCost", PartsCost);
        SetServicePartsCost.bindValue(":ServiceID", ServiceID.toDouble());

        if (SetServicePartsCost.exec() == false){
            QMessageBox::critical(this, "Erro!", SetServicePartsCost.lastError().text() + " class addservice.cpp LoadPartsAndServiceCostsGrid() ");
        }
    }
    addserviceDescriptionText();
    SumCosts();
}

void addservice::SumCosts()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Service_Hours_Duration, Service_Parts_Cost, Service_Hour_Cost, Service_Paid from Service where Service_id = " + ServiceID);

    double Service_Hours_Duration = model->data(model->index(0, 0)).toDouble(); //query result line 0 column 0
    double Service_Parts_Cost = model->data(model->index(0, 1)).toDouble(); //query result line 0 column 1
    double Service_Hour_Cost = model->data(model->index(0, 2)).toDouble(); //query result line 0 column 2

    ui->Spin_HandWorkHours->setValue(Service_Hours_Duration);
    ui->Spin_PartsCost->setValue(Service_Parts_Cost);
    ui->Spin_TotalserviceCost->setValue((Service_Hours_Duration * Service_Hour_Cost) + Service_Parts_Cost);
    ui->Spin_ServiceRegistereHandWorkHours->setValue(Service_Hour_Cost);

    //Service Paid CheckMark 0 for not Paid 1 for Paid
    bool ServicePaid = model->data(model->index(0, 3)).toBool(); //query result line 0 column 3

    if(ServicePaid){
        ui->check_Pago->setChecked(true);
    }else{
        ui->check_Pago->setChecked(false);
    }

}

void addservice::on_btn_Add_PartsUsedInTheService_clicked()
{
    partsSelectionFromList partsSelectionFromList;
    partsSelectionFromList.setServiceID(ServiceID);
    partsSelectionFromList.setModal(true);
    partsSelectionFromList.exec();

    LoadPartsAndServiceCostsGrid();
}

void addservice::on_btn_save_hoursWorked_clicked()
{
    QSqlQuery UpdateHoursWorked;
    UpdateHoursWorked.prepare("update Service set Service_Hours_Duration = :Service_Hours_Duration where Service_id = :ServiceID");

    UpdateHoursWorked.bindValue(":Service_Hours_Duration", ui->Spin_HandWorkHours->text().toDouble());
    UpdateHoursWorked.bindValue(":ServiceID", ServiceID);

    if (!(UpdateHoursWorked.exec())){
        QMessageBox::critical(this, "Erro!", UpdateHoursWorked.lastError().text() + "class addservice.cpp  on_btn_save_hoursWorked_clicked()");
    }else{
        QMessageBox::critical(this, "Sucesso!", "Horas trabalhadas atualizadas."
                                                "\nCusto do Serviço recalculadas no sistema....");
        SumCosts();
    }
}

void addservice::on_btn_atualizarDescricaoServico_clicked()
{
    Updatedservicedescription Updatedservicedescription;
    Updatedservicedescription.setServiceID(ServiceID);
    Updatedservicedescription.SetDescription();
    Updatedservicedescription.setModal(true);
    Updatedservicedescription.exec();
    addserviceDescriptionText();
}

void addservice::on_tbl_PartsUsedInService_doubleClicked(const QModelIndex &index)
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Confirmação!", "Você deseja realmente remover essa peça desse serviço?", QMessageBox::Yes|QMessageBox::No).exec())
    {
        //Bellow 2 list will retrieve the column 0 value, which is the ServicePartsUsed_id //
        const QAbstractItemModel * model = index.model();
        QVariant ServicePart_ID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);

        qDebug() << "ServicePartsUsed_id" << ServicePart_ID;
        QSqlQuery removePartsFromService;
        removePartsFromService.prepare("DELETE FROM ServicePartsUsed WHERE ServicePartsUsed_id = :ServicePartsUsed_id");
        removePartsFromService.bindValue(":ServicePartsUsed_id", ServicePart_ID.toString());
        removePartsFromService.exec();

        //RETURN PART TO STOCK//
        //Bellow 2 list will retrieve the column 0 value, which is the ServicePartsUsed_id //
        const QAbstractItemModel * model2 = index.model();
        QVariant partID = model2->data(model2->index(index.row(), 1, index.parent()), Qt::DisplayRole);
        qDebug() << "PartID" << partID;

        QSqlQuery returnPartToStock;
        returnPartToStock.prepare("UPDATE Part SET Part_Quantity = (Part_Quantity + 1) WHERE Part_id = :partID");
        returnPartToStock.bindValue(":partID", partID.toString());

        if(returnPartToStock.exec() == false){
            QMessageBox::critical(this, "Erro!", returnPartToStock.lastError().text() + "class addservice.cpp  on_btn_save_hoursWorked_clicked()");
        }
        LoadPartsAndServiceCostsGrid();
    }
}

void addservice::on_check_Pago_clicked()
{
    if(ui->check_Pago->isChecked()){
        QSqlQuery query;
        query.prepare("UPDATE Service set Service_Paid = 1 where Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, "Erro!", query.lastError().text() + "class addservice.cpp  on_check_Pago_clicked ");
        }else{
            QMessageBox::critical(this, "Ok!", "Serviço alterado para: Pago");
        }
    }else{
        QSqlQuery query;
        query.prepare("UPDATE Service set Service_Paid = 0 where Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, "Erro!", query.lastError().text() + "class addservice.cpp  on_check_Pago_clicked ");
        }else{
            QMessageBox::critical(this, "Ok!", "Serviço alterado para: Não Pago");
        }
    }
}
