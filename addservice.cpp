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


//bool addservice::verificaCamposEmBrancoNoForm()
//{
//    if (ui->txt_FullDescription->toPlainText() == "" || ui->line_ShortDescription->text() == "" )
//    {
//        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
//        QPixmap crying(":/emoticons/face-crying.png");
//        ui->lbl_Emoticon->setPixmap(crying);
//        ui->line_ShortDescription->setFocus();
//        return false;
//    }
//    //Only returns true when all the fields are filled.
//    return true;
//}

//void addservice::setClientIdandCar(QString ClientId, QString ClientCarId)
//{
//    clientid = ClientId;
//    CarID = ClientCarId;
//}

//void addservice::toggleFieldsToUpdateMode()
//{
//    ui->line_ShortDescription->setEnabled(false);
//    ui->btn_Salvar->setEnabled(false);

//    ui->btn_save_hoursWorked->setEnabled(true);
//    ui->tbl_PartsUsedInService->setEnabled(true);
//    ui->btn_Add_PartsUsedInTheService->setEnabled(true);
//    ui->check_Pago->setEnabled(true);
//    ui->btn_save_hoursWorked->setEnabled(true);
//    ui->btn_atualizarDescricaoServico->setEnabled(true);
//    ui->lbl_InsertWorkCost->setText("Atualizar horas trabalhadas: ");
////}

//void addservice::setServiceID(QString serviceid)
//{
//    ServiceID = serviceid;
//}

void addservice::on_btn_Sair_clicked()
{
    close();
}

//Check car description filed size(This function only limits entered text to 1000 chars)//
//void addservice::on_txt_FullDescription_textChanged()
//{
//    if (ui->txt_FullDescription->toPlainText().length() > 1000)
//    {
//        QString fullserviceDescription = ui->txt_FullDescription->toPlainText();
//        fullserviceDescription.chop(fullserviceDescription.length() - 1000); // Cut off at 500 characters
//        ui->txt_FullDescription->setPlainText(fullserviceDescription); // Reset text

//        // This code just resets the cursor back to the end position
//        // If you don't use this, it moves back to the beginning.
//        // This is helpful for really long text edits where you might
//        // lose your place.
//        QTextCursor cursor = ui->txt_FullDescription->textCursor();
//        cursor.setPosition(ui->txt_FullDescription->document()->characterCount() - 1);
//        ui->txt_FullDescription->setTextCursor(cursor);

//        // This is your "action" to alert the user. I'd suggest something more
//        // subtle though, or just not doing anything at all.
//        QMessageBox::critical(this, "Erro!", "Mantenha a descrição do serviço menor do que 500 letras.");
//    }
//}

//void addservice::on_btn_Salvar_clicked()
//{
//    if(verificaCamposEmBrancoNoForm()){
//        //START This block is to save current hour cost to service//
//        QSqlQueryModel* getHourCostFromDB = new QSqlQueryModel;
//        getHourCostFromDB->setQuery("select HourCost from HourCost");
//        double CurrentHourCost = getHourCostFromDB->data(getHourCostFromDB->index(0,0)).toDouble();
//        //END This block is to save current hour cost to service//

//        QSqlQuery query;
//        query.prepare("insert into Service (Service_Client_id, Service_Client_Carid, Service_Short_Description, Service_Description, Service_Hour_Cost, Service_Hours_Duration)"
//                      "values (:Service_Client_id, :Service_Client_Carid, :Service_Short_Description, :Service_Description, :Service_Hour_Cost, :Service_Hours_Duration )");

//        query.bindValue(":Service_Client_id", clientid);
//        query.bindValue(":Service_Client_Carid", CarID);
//        query.bindValue(":Service_Hour_Cost", CurrentHourCost);
//        query.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());
//        query.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());
//        //query.bindValue(":Service_Hours_Duration", ui->Spin_HandWorkHours->text().toDouble());

//        if (query.exec() == false){
//            QMessageBox::critical(this, "Erro!", query.lastError().text() + " class addservice.cpp on_btn_Salvar_clicked() ");
//        }else{
//            ui->lbl_Feedback->setText("Serviço adicionado!");
//            QPixmap cool(":/emoticons/face-cool.png");
//            ui->lbl_Emoticon->setPixmap(cool);
//            ui->line_ShortDescription->setFocus();
//            QMessageBox::information(this, "Sucesso!", "Serviço registrado para este carro e cliente."
//                                                       "\nAgora voltaremos para a tela anterior onde e a nova ordem de serviço"
//                                                       "\n estará visível. Lá você pode adicionar as peças que for usando neste"
//                                                       " serviço. As peças também pode ser adicionadas depois.");
//            ui->btn_Add_PartsUsedInTheService->setEnabled(true);
//            close();
//        }
//    }
//}

void addservice::LoadPartsAndServiceCostsGrid(){

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT ServicePartsUsed_id AS Serviço, "
                    "Part_id as 'PeçaID', "
                    "Part_Name AS 'Nome', "
                    "Part_Quantity AS 'Estoque', "
                    "Part_Cost AS 'Custo' "
                    "FROM Part p JOIN ServicePartsUsed pu "
                    "ON pu.On_Service_Part_id = p.Part_id "
                    "AND pu.Used_On_Service_id = " + ServiceID);

    if(model->query().isSelect()){
        ui->tbl_PartsUsedInService->setModel(model);
        ui->tbl_PartsUsedInService->hideColumn(0);
        ui->tbl_PartsUsedInService->hideColumn(1);
        ui->tbl_PartsUsedInService->resizeColumnsToContents();

        //Sum the Parts Used Value and add to doublespin//
        double PartsCost = 0;
        const int column = 1;
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
    SumCosts();
}

void addservice::SumCosts()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("select Service_Hours_Duration, Service_Parts_Cost, Service_Hour_Cost from Service where Service_id = " + ServiceID);

    double Service_Hours_Duration = model->data(model->index(0, 0)).toDouble(); //query result line 0 column 0
    double Service_Parts_Cost = model->data(model->index(0, 1)).toDouble(); //query result line 0 column 1
    double Service_Hour_Cost = model->data(model->index(0, 2)).toDouble(); //query result line 0 column 2

    ui->Spin_HandWorkHours->setValue(Service_Hours_Duration);
    ui->Spin_PartsCost->setValue(Service_Parts_Cost);
    ui->Spin_TotalserviceCost->setValue((Service_Hours_Duration * Service_Hour_Cost) + Service_Parts_Cost);
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

//void addservice::on_btn_atualizarDescricaoServico_clicked()
//{
//    CreateServiceDescription CreateServiceDescription;
//    CreateServiceDescription.SetDescription();


//    EnableDescriptionUpdate();
//}

void addservice::on_btn_atualizarDescricaoServico_clicked()
{
    Updatedservicedescription Updatedservicedescription;
    Updatedservicedescription.setServiceID(ServiceID);
    Updatedservicedescription.SetDescription();
    Updatedservicedescription.setModal(true);
    Updatedservicedescription.exec();
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
