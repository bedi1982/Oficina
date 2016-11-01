#include "addclientcar.h"
#include "ui_addclientcar.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "clientinfo.h"
QString client;

addclientcar::addclientcar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addclientcar)
{
    ui->setupUi(this);
}

addclientcar::~addclientcar()
{
    delete ui;
}

void addclientcar::Setclient(QString client_id){
    client = client_id;
}

bool addclientcar::verificaCamposEmBrancoNoForm()
{
    if (   ui->txt_ModeloCarro->toPlainText() == ""
           ||ui->txt_AnoCarro->toPlainText() == ""
           ||ui->txt_carDescription->toPlainText() == ""
           ||ui->txt_PlacaCarro_->toPlainText() == ""
           ||ui->txt_CordoCarro->toPlainText()== ""
           )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        limpaForm();
        ui->txt_ModeloCarro->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addclientcar::addClientInfoToForm(QString client_id){
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
    }
    while(query.next())
    {
        ui->txt_NomeCliente->setText(query.value(1).toString());
    }

}

void addclientcar::limpaForm()
{
    ui->txt_ModeloCarro->setText("");
    ui->txt_AnoCarro->setText("");
    ui->txt_carDescription->setText("");
    ui->txt_PlacaCarro_->setText("");
    ui->txt_CordoCarro->setText("");
}

void addclientcar::addCar(QString client_id){
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into ClientCar (ClientCar_Client_id, ClientCar_Model, ClientCar_Description, ClientCar_BuiltYear, ClientCar_Placa, ClientCar_Color)"
                      "values (:ClientId, :Model, :Description, :BuiltYear, :Placa, :Color)");

        query.bindValue(":ClientId", client_id);
        query.bindValue(":Model", ui->txt_carDescription->toPlainText());
        query.bindValue(":Description", ui->txt_carDescription->toPlainText());
        query.bindValue(":BuiltYear", ui->txt_AnoCarro->toPlainText());
        query.bindValue(":Placa", ui->txt_PlacaCarro_->toPlainText());
        query.bindValue(":Color", ui->txt_CordoCarro->toPlainText());

        if (query.exec() == false){
            qDebug() << query.lastError();
        }
        ui->lbl_Feedback->setText("Carro adicionado ao Cliente!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        ui->txt_ModeloCarro->setFocus();
    }
}

void addclientcar::on_btn_Adcionar_clicked()
{
 addCar(client);
}
