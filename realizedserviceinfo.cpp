#include "realizedserviceinfo.h"
#include "ui_realizedserviceinfo.h"
#include "partsusedonservice.h"
#include "QSqlQuery"
#include "QDebug"
#include "QMessageBox"
#include "QSqlError"

QString ServiceID;

realizedServiceInfo::realizedServiceInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::realizedServiceInfo)
{
    ui->setupUi(this);
}

realizedServiceInfo::~realizedServiceInfo()
{
    delete ui;
}

void realizedServiceInfo::on_btn_Add_PartsUsedInTheService_clicked()
{
    partsUsedOnService partsUsedOnService;
    //addclientcar addclientcar;
    //addclientcar.Setclient(client_id);
    //addclientcar.addClientInfoToForm(client_id);
    partsUsedOnService.setModal(true);
    partsUsedOnService.exec();
}

void realizedServiceInfo::setServiceID(QString service_id){
    ServiceID = service_id;
}

void realizedServiceInfo::loadAll(){

    {
        QSqlQuery query;

        query.prepare("SELECT * from Service where Service_id = " + ServiceID);

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, "Erro!", query.lastError().text() + ". Class: realizedserviceinfo.cpp46");
        }else{
            while(query.next())
            {
                ui->line_ShortDescription->setText(query.value(4).toString());
                ui->txt_FullDescription->setText(query.value(5).toString());
                ui->lbl_date->setText(query.value(11).toString());
            }
        }
    }
}
