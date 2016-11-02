#include "clientinfo.h"
#include "ui_clientinfo.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "addclientcar.h"
#include "addservice.h"

#include <QSqlTableModel>
#include "QDebug"
#include "QSqlRelationalTableModel"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QMessageBox"

QString client_id;

clientinfo::clientinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientinfo)
{
    ui->setupUi(this);

    QPixmap service(":/emoticons/service.png");
    ui->lbl_ServiceIcon->setPixmap(service);

    QPixmap carKey(":/emoticons/carkey.png");
    ui->lbl_NewCarIcon->setPixmap(carKey);
}

clientinfo::~clientinfo()
{
    delete ui;
}

void clientinfo::setClient_Id(QString id)
{
    client_id = id;
}

void clientinfo::loadAll(){
    loadCarsGrid();
    loadServicesGrid();
    loadClientInfo_to_TextBoxes();
}

void clientinfo::loadClientInfo_to_TextBoxes()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, "Erro!", "Este carro não foi adicionado!!(class clientinfo.cpp).");
    }else{

    while(query.next())
    {
        ui->txt_clientName->setText(query.value(1).toString());
        ui->txt_clientPhone->setText(query.value(6).toString());
        ui->txt_clientAddress->setText(query.value(2).toString());
        ui->txt_clientSince->setText(query.value(8).toString());
    }
    }
}

void clientinfo::loadServicesGrid()
{    
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Service");
    model->setFilter("Service_Client_id = " + client_id);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tbl_ClientServices->setModel(model);
}

void clientinfo::loadCarsGrid()
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("ClientCar");
    model->setFilter("ClientCar_Client_id = " + client_id);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tbl_clientCars->setModel(model);
}

void clientinfo::on_btn_addClientCarro_clicked()
{
    addclientcar addclientcar;
    addclientcar.Setclient(client_id);
    addclientcar.addClientInfoToForm(client_id);
    addclientcar.setModal(true);
    addclientcar.exec();
    loadCarsGrid();
}

//Adding Service to this client and this car//
void clientinfo::on_tbl_clientCars_doubleClicked(const QModelIndex &index)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = index.model();
    QVariant carID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);
    addservice addservice;
    addservice.setClientIdandCar(client_id, carID.toString());
    addservice.setModal(true);
    addservice.exec();
    loadServicesGrid();
}
