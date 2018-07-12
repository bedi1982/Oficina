#include "Client_Services_History.h"
#include "ui_Client_Services_History.h"

#include "Client_Add_Car.h"
#include "Client_Add_Service.h"

#include "Client_Update.h"
#include "Service_Create_Description.h"
#include "System_Services_and_Info.h"

#include <QSqlTableModel>
#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"
#include "QSettings"
#include "QMessageBox"

Client_Services_History::Client_Services_History(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Services_History)
{
    ui->setupUi(this);
    LoadSettings();
    ui->tabWidget->setCurrentIndex(0);//Focus on the cars
}

Client_Services_History::~Client_Services_History()
{
    SaveSettings();
    delete ui;
}

QString Client_Services_History::getClient_id() const
{
    return client_id;
}

void Client_Services_History::setClient_id(const QString &value)
{
    client_id = value;
    loadAll();
}

void Client_Services_History::loadAll(){
    load_Cars_Grid();
    Load_Services_Grid();
    Load_Client_Info_To_Text_Boxes();
}

void Client_Services_History::Load_Client_Info_To_Text_Boxes()
{
    QSqlQuery query;
    query.prepare("SELECT Client_Name FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        QMessageBox::critical(this, tr("Erro!"), query.lastError().text() +
                              "class Client_Services_History::loadClientInfo_to_TextBoxes() ");
    }else{
        while(query.next())
        {
            this->setWindowTitle("Client: " + query.value(0).toString());
        }
    }
}

void Client_Services_History::Load_Services_Grid()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT"
                    " Service_id,"
                    " ClientCar_Model,"
                    " ClientCar_Plate,"
                    " Service_Short_Description,"
                    " Service_Parts_Cost,"
                    " Service_Hours_Duration,"
                    " Service_Hour_Cost,"
                    " Service_Paid,"
                    " Service_Finished,"
                    " Service_created_at,"
                    " Service_updated_at"
                    " FROM Service s JOIN ClientCar cc"
                    " ON s.Service_Client_Carid = cc.ClientCar_id AND Service_Client_id = " + client_id +
                    " order by 1 DESC");
    model->setHeaderData(0, Qt::Horizontal, tr("Service ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("On Car"));
    model->setHeaderData(2, Qt::Horizontal, tr("Plate"));
    model->setHeaderData(3, Qt::Horizontal, tr("Short Description"));
    model->setHeaderData(4, Qt::Horizontal, tr("Parts Cost"));
    model->setHeaderData(5, Qt::Horizontal, tr("Hours Worked"));
    model->setHeaderData(6, Qt::Horizontal, tr("Hour Cost"));
    model->setHeaderData(7, Qt::Horizontal, tr("Paid?"));
    model->setHeaderData(8, Qt::Horizontal, tr("Finished?"));
    model->setHeaderData(9, Qt::Horizontal, tr("Created"));
    model->setHeaderData(10, Qt::Horizontal, tr("Updated"));

    if(model->query().isSelect()){
        ui->tbl_Client_Services->setModel(model);
        //ui->tbl_Client_Services->sortByColumn(2, Qt::DescendingOrder);
        ui->tbl_Client_Services->resizeColumnsToContents();
    }else{
        QMessageBox::critical(this, tr("Error!"), model->query().lastError().text() +
                              "class Client_Services_History::loadServicesGrid()");
    }
}

void Client_Services_History::load_Cars_Grid()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT"
                    " ClientCar_id,"
                    " ClientCar_Model,"
                    " ClientCar_Plate,"
                    " ClientCar_BuiltYear,"
                    " ClientCar_Color,"
                    " ClientCar_created_at,"
                    " ClientCar_updated_at"
                    " FROM ClientCar WHERE ClientCar_Client_id = " + client_id +
                    " ORDER BY ClientCar_id desc");

    model->setHeaderData(0, Qt::Horizontal, tr("Car ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Car Model"));
    model->setHeaderData(2, Qt::Horizontal, tr("Plate"));
    model->setHeaderData(3, Qt::Horizontal, tr("Built Year"));
    model->setHeaderData(4, Qt::Horizontal, tr("Color"));
    model->setHeaderData(5, Qt::Horizontal, tr("Created At"));
    model->setHeaderData(6, Qt::Horizontal, tr("Updated At"));

    if(model->query().isSelect()){
        //ui->tbl_Client_Cars->setStyleSheet("QHeaderView::section { background-color:red }"); // Colors test :: a playground//
        ui->tbl_Client_Cars->setModel(model);
        ui->tbl_Client_Cars->resizeColumnsToContents();

        if(model->rowCount() <= 0){
            if (QMessageBox::Yes == QMessageBox(QMessageBox::Question, "Question", "This Client has no Car registered Currently. "
                                                "Would you like to add one?", QMessageBox::Yes|QMessageBox::No).exec())
            {
                on_btn_Add_Car_To_Client_clicked();
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error!"), model->query().lastError().text() + "class Client_Services_History::loadCarsGrid() ");
    }
}

//Adding Service to this client and this car//
void Client_Services_History::on_tbl_Client_Cars_doubleClicked(const QModelIndex &index)
{
    //Bellow 2 list will retrieve the column 0 value, which is the ServiceID//
    const QAbstractItemModel * model = index.model();
    QVariant carID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);

    Service_Create_Description Service_Create_Description;
    Service_Create_Description.setCarID(carID.toString());
    Service_Create_Description.setClientid(client_id);

    Service_Create_Description.exec();
    Load_Services_Grid();
    ui->tabWidget->setCurrentIndex(1); //Move to services tab
}

void Client_Services_History::on_tbl_Client_Services_doubleClicked(const QModelIndex &index)
{   //You come to this function from double clicking Services on the clientinfo Grid//
    //Bellow 3 lines will retrieve the column 0 (ServiceID) and column2 (CarID) values from the Grid//
    const QAbstractItemModel * model = index.model();
    QVariant ServiceID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);
    QVariant CarID = model->data(model->index(index.row(), 2, index.parent()), Qt::DisplayRole);

    Client_Add_Service Client_Add_Service;
    Client_Add_Service.setCarID(CarID.toString());
    Client_Add_Service.setServiceID(ServiceID.toString());
    Client_Add_Service.setClientid(client_id);
    Client_Add_Service.Load_Parts_And_Service_Costs_Grid();

    Client_Add_Service.exec();
    Load_Services_Grid();
}

void Client_Services_History::on_btn_Update_Client_clicked()
{
    Client_Update Client_Update;
    Client_Update.setClient_id(client_id);
    Client_Update.load_Client_Info_To_TextBoxes();
    Client_Update.exec();
    Load_Client_Info_To_Text_Boxes();
}

void Client_Services_History::on_btn_Add_Car_To_Client_clicked()
{
    Client_Add_Car Client_Add_Car;
    Client_Add_Car.setClient(client_id);
    Client_Add_Car.Add_Client_Info_To_Form(client_id);
    Client_Add_Car.exec();
    load_Cars_Grid();
}

void Client_Services_History::on_Close_clicked()
{
    close();
}


void Client_Services_History::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Services_History");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Client_Services_History::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Services_History");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
