#include "addservice.h"
#include "ui_addservice.h"
#include "partsselectionfromlist.h"
#include "mainwindow.h"
#include "QMessageBox"

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"

QString clientid;
QString CarID;
QString ServiceID;

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

bool addservice::verificaCamposEmBrancoNoForm()
{
    if (ui->txt_FullDescription->toPlainText() == "" || ui->line_ShortDescription->text() == "" )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->line_ShortDescription->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addservice::setClientIdandCar(QString ClientId, QString ClientCarId)
{
    clientid = ClientId;
    CarID = ClientCarId;
}

void addservice::toggleFieldsToUpdateMode()
{
    ui->line_ShortDescription->setEnabled(false);
    ui->txt_FullDescription->setEnabled(false);
    ui->btn_Salvar->setEnabled(false);
    ui->Spin_HandWorkCost->setEnabled(false);

    ui->tbl_PartsUsedInService->setEnabled(true);
    ui->btn_Add_PartsUsedInTheService->setEnabled(true);
    ui->check_Pago->setEnabled(true);
}

void addservice::setServiceID(QString serviceid)
{
    ServiceID = serviceid;
}

void addservice::on_btn_Sair_clicked()
{
    close();
}

//Check car description filed size(This function only limits entered text to 1000 chars)//
void addservice::on_txt_FullDescription_textChanged()
{
    if (ui->txt_FullDescription->toPlainText().length() > 1000)
    {
        QString fullserviceDescription = ui->txt_FullDescription->toPlainText();
        fullserviceDescription.chop(fullserviceDescription.length() - 1000); // Cut off at 500 characters
        ui->txt_FullDescription->setPlainText(fullserviceDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_FullDescription->textCursor();
        cursor.setPosition(ui->txt_FullDescription->document()->characterCount() - 1);
        ui->txt_FullDescription->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::critical(this, "Erro!", "Mantenha a descrição do serviço menor do que 500 letras.");
    }
}

void addservice::on_btn_Salvar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into Service (Service_Client_id, Service_Client_Carid, Service_Short_Description, Service_Description)"
                                   "values (:Service_Client_id, :Service_Client_Carid, :Service_Short_Description, :Service_Description )");

        query.bindValue(":Service_Client_id", clientid);
        query.bindValue(":Service_Client_Carid", CarID);
        query.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());
        query.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());

        if (query.exec() == false){
            QMessageBox::critical(this, "Erro!", query.lastError().text() + " class addservice.cpp on_btn_Salvar_clicked() ");
        }else{
            ui->lbl_Feedback->setText("Serviço adicionado!");
            QPixmap cool(":/emoticons/face-cool.png");
            ui->lbl_Emoticon->setPixmap(cool);
            ui->line_ShortDescription->setFocus();
            QMessageBox::information(this, "Sucesso!", "Serviço registrado para este carro Agora você pode adicionar as peças que usou neste serviço.");
            ui->btn_Add_PartsUsedInTheService->setEnabled(true);
            close();
        }
    }
}

void addservice::LoadPartsGrid(){

    QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery("SELECT Part_Name AS Nome, "
                        "Part_Description AS Descriçao , "
                        "Part_Cost AS Custo, "
                        "pu.Quantity AS Quantidade "
                        "FROM Part p JOIN ServicePartsUsed pu "
                        "ON pu.Part_id = p.Part_id "
                        "AND pu.Used_On_Service_id =" + ServiceID);

        if(model->query().isSelect()){
            ui->tbl_PartsUsedInService->setModel(model);
            ui->tbl_PartsUsedInService->resizeColumnsToContents();
}}

void addservice::on_btn_Add_PartsUsedInTheService_clicked()
{
    partsSelectionFromList partsSelectionFromList;
    partsSelectionFromList.setServiceID(ServiceID);

    QMessageBox::information(this, "peça adicionanda!", ServiceID);

    partsSelectionFromList.setModal(true);
    partsSelectionFromList.exec();
    LoadPartsGrid();
}
