#include "QMessageBox"
#include "QtSql"

#include "Client_Add_Service.h"
#include "ui_Client_Add_service.h"
#include "Stock_Parts_Selection.h"
#include "Service_Update_Description.h"
#include "Main_Window.h"

Client_Add_Service::Client_Add_Service(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add_Service)
{
    ui->setupUi(this);
    LoadSettings();
    ui->txt_Servicedescription->setReadOnly(true);
    ui->line_ServiceShortDescription->setReadOnly(true);
    ui->tabWidget->setCurrentIndex(0);//Focus on the first tab//
}

Client_Add_Service::~Client_Add_Service()
{
    SaveSettings();
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

void Client_Add_Service::Add_Service_Description_Text(){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT Service_Description, Service_Short_Description FROM Service WHERE Service_id = " + ServiceID);

    ui->line_ServiceShortDescription->setText(model->data(model->index(0, 1)).toString());
    ui->txt_Servicedescription->setText(model->data(model->index(0, 0)).toString());
}

void Client_Add_Service::Load_Parts_And_Service_Costs_Grid(){

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT ServicePartsUsed_id,"
                    " Part_id,"
                    " Part_Quantity,"
                    " Part_Name, "
                    " Part_Cost"
                    " FROM Part p JOIN ServicePartsUsed pu "
                    " ON pu.Used_Part_ID = p.Part_id "
                    " AND pu.Used_On_What_Service_id = " + ServiceID);

    model->setHeaderData(0, Qt::Horizontal, tr("Used Service Part ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Part ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("Part Quantity"));
    model->setHeaderData(3, Qt::Horizontal, tr("Part Name"));
    model->setHeaderData(4, Qt::Horizontal, tr("Part Cost"));

    if(model->query().isSelect()){

        //the model is also used bellow at: on_tbl_Parts_Used_In_Service_doubleClicked()//
        ui->tbl_Parts_Used_In_Service->setModel(model);

        //Next 3 lines: Usefull info, but noise for the user, so we hide//
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
        SetServicePartsCost.prepare("update Service set Service_Parts_Cost = :PartsCost WHERE Service_id = " + ServiceID);
        SetServicePartsCost.bindValue(":PartsCost", PartsCost);

        if (SetServicePartsCost.exec() == false){
            QMessageBox::critical(this, tr("Error!"), SetServicePartsCost.lastError().text() + " class Client_Add_Service::LoadPartsAndServiceCostsGrid() ");
        }
    }
    Add_Service_Description_Text();
    Sum_Costs();
}

void Client_Add_Service::Sum_Costs()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT Service_Hours_Duration, Service_Parts_Cost, Service_Hour_Cost, Service_Paid, Service_Finished FROM Service WHERE Service_id = " + ServiceID);

    double Hand_Work_Hours = model->data(model->index(0, 0)).toDouble(); //query result line 0 column 0
    double Service_Parts_Cost = model->data(model->index(0, 1)).toDouble(); //query result line 0 column 1
    double Service_Hour_Cost = model->data(model->index(0, 2)).toDouble(); //query result line 0 column 2

    ui->double_Service_Hour_Cost->setValue(Service_Hour_Cost);
    ui->lcd_Service_Hour_Cost->display(Service_Hour_Cost);

    ui->Spin_Hand_Work_Hours->setValue(Hand_Work_Hours);
    //ui->Spin_PartsCost->setValue(Service_Parts_Cost);
    //ui->Spin_TotalserviceCost->setValue((Service_Hours_Duration * Service_Hour_Cost) + Service_Parts_Cost);
    //ui->Spin_ServiceRegistereHandWorkHours->setValue(Service_Hour_Cost);
    ui->lcd_Parts_Cost->display(Service_Parts_Cost);
    ui->lcd_Parts_Cost_2->display(Service_Parts_Cost);
    ui->lcd_Hour_cost->display(Hand_Work_Hours * Service_Hour_Cost);
    ui->lcd_Service_Total->display((Hand_Work_Hours * Service_Hour_Cost) + Service_Parts_Cost);

    //Service_Paid CheckMark 0 for not Paid 1 for Paid
    bool Service_Paid = model->data(model->index(0, 3)).toBool(); //query result line 0 column 3

    if(Service_Paid){
        ui->check_Paid->setChecked(true);
    }else{
        ui->check_Paid->setChecked(false);
    }

    //Service_Finished CheckMark 0 for not Finished 1 for Finished
    bool Service_Finished = model->data(model->index(0, 4)).toBool(); //query result line 0 column 4

    if(Service_Finished){
        ui->check_Finished->setChecked(true);
    }else{
        ui->check_Finished->setChecked(false);
    }
}

void Client_Add_Service::on_btn_Add_Parts_Used_In_The_Service_clicked()
{
    Stock_Parts_Selection Stock_Parts_Selection;
    Stock_Parts_Selection.setServiceID(ServiceID);
    Stock_Parts_Selection.exec();

    Load_Parts_And_Service_Costs_Grid();
}

void Client_Add_Service::on_tbl_Parts_Used_In_Service_doubleClicked(const QModelIndex &index)
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, tr("Confirmation!"), tr("Do you really want to remove this Part from the Service?"), QMessageBox::Yes|QMessageBox::No).exec())
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
            QMessageBox::critical(this, tr("Error!"), returnPartToStock.lastError().text() + "class addservice.cpp  on_btn_save_hoursWorked_clicked()");
        }
        Load_Parts_And_Service_Costs_Grid();
    }
}

void Client_Add_Service::on_check_Paid_clicked()
{
    if(ui->check_Paid->isChecked()){
        QSqlQuery query;
        query.prepare("UPDATE Service SET Service_Paid = 1 WHERE Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class addservice.cpp  on_check_Pago_clicked ");
        }else{
            QMessageBox::information(this, tr("Paid?!"), tr("Service switched to:\n Paid"));
        }
    }else{
        QSqlQuery query;
        query.prepare("UPDATE Service SET Service_Paid = 0 WHERE Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class addservice.cpp on_check_Pago_clicked(not checked) ");
        }else{
            QMessageBox::information(this, tr("Paid?"), tr("Service switched to:\n Not Paid"));
        }
    }
}

void Client_Add_Service::on_check_Finished_clicked()
{
    if(ui->check_Finished->isChecked()){
        QSqlQuery query;
        query.prepare("UPDATE Service SET Service_Finished = 1 WHERE Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class addservice.cpp  on_check_Finished_clicked ");
        }else{
            QMessageBox::information(this, tr("Finished?!"), tr("Service switched to:\nFinished"));
        }
    }else{
        QSqlQuery query;
        query.prepare("UPDATE Service SET Service_Finished = 0 WHERE Service_Id = " + ServiceID);
        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class addservice.cpp on_check_Finished_clicked() ");
        }else{
            QMessageBox::information(this, tr("Finished?"), tr("Service switched to:\nNot finished"));
        }
    }
}


void Client_Add_Service::on_btn_Update_Service_description_clicked()
{
    Service_Update_Description service_Update_Description;
    service_Update_Description.setServiceID(ServiceID);
    service_Update_Description.Set_Description();
    service_Update_Description.exec();
    Add_Service_Description_Text();
}

void Client_Add_Service::on_btnBox_Close_rejected()
{
    close();
}

void Client_Add_Service::on_Spin_Hand_Work_Hours_valueChanged()
{
    QSqlQuery Update_Hours_Worked;
    Update_Hours_Worked.prepare("UPDATE Service SET Service_Hours_Duration = :Service_Hours_Duration WHERE Service_id = " + ServiceID);

    Update_Hours_Worked.bindValue(":Service_Hours_Duration", ui->Spin_Hand_Work_Hours->value());

    if (!(Update_Hours_Worked.exec())){
        QMessageBox::critical(this, tr("Error!"), Update_Hours_Worked.lastError().text() + "class Client_Add_Service::on_btn_save_hoursWorked_clicked()");
    }else{
        Sum_Costs();
    }
}

//TODO :: Work In progress TODO//
void Client_Add_Service::on_dateTimeEdit_dateTimeChanged()
{
    QSqlQuery query;
    //query.prepare("UPDATE Service SET Service_Client_Will_Retrieve_At " + dateTime.toString("yyyy-MM-dd hh:mm:ss"));

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class addservice.cpp  on_check_Finished_clicked ");
    }else{
        QMessageBox::information(this, tr("Ok!"), tr("Vehicle Retrieval Date Set..."));
    }
}

void Client_Add_Service::on_Button_Apply_new_Hour_Cost_clicked()
{
    QSqlQuery Update_Service_Cost;
    Update_Service_Cost.prepare("UPDATE Service SET Service_Hour_Cost = :Service_Hour_Cost WHERE Service_id = " + ServiceID);

    Update_Service_Cost.bindValue(":Service_Hour_Cost", ui->double_Service_Hour_Cost->value());

    if (!(Update_Service_Cost.exec())){
        QMessageBox::critical(this, tr("Error!"), Update_Service_Cost.lastError().text() + "class Client_Add_Service::on_Button_Apply_new_Hour_Cost_clicked()");
    }else{
        QMessageBox::information(this, tr("Ok!"), tr("Service Hour Cost for this service updated..."));
        Load_Parts_And_Service_Costs_Grid();
        Sum_Costs();
    }
}

void Client_Add_Service::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Add_Service");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Client_Add_Service::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Add_Service");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}

void Client_Add_Service::on_buttonBox_Close_rejected()
{
    close();
}
