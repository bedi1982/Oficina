#include "clientinfo.h"
#include "ui_clientinfo.h"
#include "QDebug"
#include "addclientcar.h"
#include "addservice.h"

#include <QSqlTableModel>
#include "QDebug"
#include "QSqlRelationalTableModel"
#include "QSqlQuery"
#include "QMessageBox"
#include "QSqlError"
#include "editclient.h"
#include "createservicedescription.h"

clientinfo::clientinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientinfo)
{
    ui->setupUi(this);

    QPixmap service(":/emoticons/service.png");
    ui->lbl_ServiceIcon->setPixmap(service);

    QPixmap carKey(":/emoticons/carkey.png");
    ui->lbl_NewCarIcon->setPixmap(carKey);

    QPixmap clienticon(":/emoticons/client_info.png");
    ui->lbl_ClientInfo->setPixmap(clienticon);
}

clientinfo::~clientinfo()
{
    delete ui;
}

QString clientinfo::getClient_id() const
{
    return client_id;
}

void clientinfo::setClient_id(const QString &value)
{
    client_id = value;
}

void clientinfo::loadAll(){
    loadCarsGrid();
    loadServicesGrid();
    loadClientInfo_to_TextBoxes();
}

void clientinfo::loadClientInfo_to_TextBoxes()
{
    QSqlQuery query;
    query.prepare("SELECT Client_id, Client_Name, Client_Address, Client_Phone, Client_City FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, "Erro!", query.lastError().text() + "class clientinfo.cpp loadClientInfo_to_TextBoxes() ");
    }else{
        while(query.next())
        {
            ui->line_ClientID->setText(query.value(0).toString());
            ui->line_Name->setText(query.value(1).toString());
            ui->line_Address->setText(query.value(2).toString());
            ui->line_Phone->setText(query.value(3).toString());
            ui->line_ClientCity->setText(query.value(4).toString());
        }
    }
}

void clientinfo::loadServicesGrid()
{    
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT "
                    "Service_id AS ID,"
                    "ClientCar_Model AS Carro, "
                    "ClientCar_Placa AS Placa, "
                    "Service_Short_Description AS 'Título do Serviço', "
                    "Service_Parts_Cost AS 'Custo das Peças', "
                    "Service_Hours_Duration AS 'Horas Trabalhadas', "
                    "Service_Hour_Cost AS 'Custo p/ Hora', "
                    "Service_Paid AS Pago, "
                    "Service_created_at AS 'Executado em' "
                    "FROM Service s JOIN ClientCar cc "
                    "ON s.Service_Client_Carid = cc.ClientCar_id AND Service_Client_id = " + client_id +
                    " order by 9 desc");

    if(model->query().isSelect()){
        ui->tbl_ClientServices->setModel(model);
        ui->tbl_ClientServices->sortByColumn(0, Qt::DescendingOrder);
        ui->tbl_ClientServices->resizeColumnsToContents();
    }else{
        QMessageBox::critical(this, "Erro!", model->query().lastError().text() + "class clientinfo.cpp loadServicesGrid() ");
    }
}

void clientinfo::loadCarsGrid()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT "
                    "ClientCar_id as 'ID',"
                    "ClientCar_Model as Carro,"
                    "ClientCar_Placa as Placa,"
                    "ClientCar_BuiltYear as 'Ano de Fabricação',"
                    "ClientCar_Color as Cor,"
                    "ClientCar_created_at as 'Adicionado em'"
                    "FROM ClientCar where ClientCar_Client_id = " + client_id +
                    " order by 6 desc");

    if(model->query().isSelect()){
        ui->tbl_clientCars->setModel(model);
        ui->tbl_clientCars->resizeColumnsToContents();
        ui->tbl_clientCars->sortByColumn(0, Qt::DescendingOrder);
        // ui->tbl_clientCars->hideColumn(0);
    }else{
        QMessageBox::critical(this, "Erro!", model->query().lastError().text() + "class clientinfo.cpp loadCarsGrid() ");
    }
}

void clientinfo::on_btn_addClientCarro_clicked()
{
    addclientcar addclientcar;
    addclientcar.setClient(client_id);
    addclientcar.addClientInfoToForm(client_id);
    addclientcar.setModal(true);
    addclientcar.exec();
    loadCarsGrid();
}

//Adding Service to this client and this car//
void clientinfo::on_tbl_clientCars_doubleClicked(const QModelIndex &index)
{
    //Bellow 2 list will retrieve the column 0 value, which is the ServiceID//
    const QAbstractItemModel * model = index.model();
    QVariant carID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);

    CreateServiceDescription CreateServiceDescription;
    CreateServiceDescription.setCarID(carID.toString());
    CreateServiceDescription.setClientid(client_id);

    CreateServiceDescription.setModal(true);
    CreateServiceDescription.exec();
    loadServicesGrid();
}

void clientinfo::on_tbl_ClientServices_doubleClicked(const QModelIndex &index)
{   //You come to this function from double clicking Services on the clientinfo Grid//
    //Bellow 2 lines will retrieve the column 0 (ServiceID)value from the Grid//
    const QAbstractItemModel * model = index.model();

    QVariant ServiceID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);
    //QVariant ClientID = model->data(model->index(index.row(), 1, index.parent()), Qt::DisplayRole);
    QVariant CarID = model->data(model->index(index.row(), 2, index.parent()), Qt::DisplayRole);

    addservice addservice;
    addservice.setCarID(CarID.toString());
    addservice.setServiceID(ServiceID.toString());
    addservice.setClientid(client_id);
    addservice.LoadPartsAndServiceCostsGrid();

    addservice.setModal(true);
    addservice.exec();
    loadServicesGrid();
}

void clientinfo::on_btn_atualizarCliente_clicked()
{
    EditClient EditClient;
    EditClient.LoadEditableGrid(client_id);
    EditClient.setModal(true);
    EditClient.exec();
    loadClientInfo_to_TextBoxes();
}
