#include "Client_Services_History.h"
#include "Client_Add_Car.h"
#include "Client_Add_Service.h"
#include "Client_Update.h"

#include "System_Services_and_Info.h"

#include "Service_Create_Description.h"

#include <ui_Client_Services_History.h>
#include "ui_Client_Services_History.h"

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
    ui->tab_Client_History->setCurrentIndex(1);
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
    load_Client_Info_Tab();
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
            if (QMessageBox::Yes == QMessageBox(QMessageBox::Question, "Question", "This client has no car. "
                                                "Would you like to add one?", QMessageBox::Yes|QMessageBox::No).exec())
            {
                on_btn_Add_Car_To_Client_clicked();
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error!"), model->query().lastError().text() + "class Client_Services_History::loadCarsGrid() ");
    }
}

void Client_Services_History::load_Client_Info_Tab()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class Client_Edit::loadClientInfo_to_TextBoxes() ");
    }else{
        while(query.next())
        {
            ui->line_SysID->setText(query.value(0).toString()); //SystemID
            ui->line_Name->setText(query.value(1).toString()); //Name
            this->setWindowTitle("Client: " + query.value(1).toString()); //Add client name to window title
            ui->line_Address->setText(query.value(2).toString()); //Adress
            ui->line_City->setText(query.value(3).toString()); //City
            ui->line_Personal_ID->setText(query.value(5).toString()); // Personal ID
            ui->line_Phone->setText(query.value(6).toString()); //Phone
            ui->line_Updated_At->setText(query.value(7).toString()); //updated At
            ui->line_Created_At->setText(query.value(8).toString()); //created At
        }
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
    ui->tab_Client_History->setCurrentIndex(1); //Move to services tab
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
    QSqlQuery query;
    query.prepare(" UPDATE Client SET "
                  "  Client_Name = :Client_Name"
                  " ,Client_Address = :Client_Address"
                  " ,Client_City = :Client_City"
                  " ,Client_ID_Number = :Client_ID_Number"
                  " ,Client_Phone = :Client_Phone"
                  " WHERE Client_id = " + client_id);

    query.bindValue(":Client_Name", ui->line_Name->text());
    query.bindValue(":Client_Address", ui->line_Address->text());
    query.bindValue(":Client_City", ui->line_City->text());
    query.bindValue(":Client_ID_Number", ui->line_Personal_ID->text());
    query.bindValue(":Client_Phone", ui->line_Phone->text());

    if (query.exec()) {
        QMessageBox::information(this, tr("Success"), tr("Client Updated!"));
        load_Client_Info_Tab();
    } else {
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class Client_Edit::on_btn_update_clicked() ");
    }
}

void Client_Services_History::on_btn_Add_Car_To_Client_clicked()
{
    Client_Add_Car Client_Add_Car;
    Client_Add_Car.setClient(client_id);
    Client_Add_Car.Add_Client_Info_To_Form(client_id);
    Client_Add_Car.exec();
    load_Cars_Grid();
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

void Client_Services_History::on_btn_CLose_clicked()
{
    close();
}
