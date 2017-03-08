#include "Client_Add_Car.h"
#include "ui_Client_Add_Car.h"
#include "Client_Services_History.h"
#include "System_Services_and_Info.h"

#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"

#include "QMessageBox"

Client_Add_Car::Client_Add_Car(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add_Car)
{
    ui->setupUi(this);
}

Client_Add_Car::~Client_Add_Car()
{
    delete ui;
}

bool Client_Add_Car::Verify_Empty_Fields_On_Form()
{
    if (   ui->txt_Car_Model->text() == ""
           ||ui->txt_Car_Year->text() == ""
           ||ui->txt_Full_Car_Description->toPlainText() == ""
           ||ui->txt_Car_Plate->text() == ""
           ||ui->txt_Car_Color->text()== ""
           )
    {
        ui->txt_Car_Model->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Client_Add_Car::Add_Client_Info_To_Form(QString client_id){
    QSqlQuery query;
    query.prepare("SELECT Client_Name FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". Class: Class: Client_Add_Car.addClientInfoToForm(QString client_id)");
    }

    while(query.next()){
        ui->line_Client_Name->setText(query.value(0).toString());
    }
}

void Client_Add_Car::Add_Car(QString client_id){
    if(Verify_Empty_Fields_On_Form()){
        QSqlQuery query;
        query.prepare("INSERT INTO ClientCar (ClientCar_Client_id, ClientCar_Model, ClientCar_Description, ClientCar_BuiltYear, ClientCar_Plate, ClientCar_Color)"
                      "values (:ClientId, :Model, :Description, :BuiltYear, :Plate, :Color)");

        query.bindValue(":ClientId", client_id);
        query.bindValue(":Model", ui->txt_Car_Model->text());
        query.bindValue(":Description", ui->txt_Full_Car_Description->toPlainText());
        query.bindValue(":BuiltYear", ui->txt_Car_Year->text());
        query.bindValue(":Plate", ui->txt_Car_Plate->text());
        query.bindValue(":Color", ui->txt_Car_Color->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". Class: Client_Add_Car.addCar(QString client_id)");
        }else{
            QMessageBox::information(this, tr("Success!"), tr("Client's Car added."));
            close();
        }
    }
}

//Check car description size is smaller then 250//
void Client_Add_Car::Check_Car_Description_Size(){

    const int max_size = 250;

    if(ui->txt_Full_Car_Description->toPlainText().length() > max_size){
        ui->txt_Full_Car_Description->setPlainText(System_Services_and_Info::Check_Text_Size(max_size, ui->txt_Full_Car_Description->toPlainText()));

        //Warn the user:
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the text shorter then %1 chars.").arg(max_size));

        //Put cursor back to the end of the text//
        QTextCursor cursor = ui->txt_Full_Car_Description->textCursor();
        cursor.setPosition(ui->txt_Full_Car_Description->document()->characterCount() - 1);
        ui->txt_Full_Car_Description->setTextCursor(cursor);
    }
}

QString Client_Add_Car::getClient() const
{
    return client;
}

void Client_Add_Car::setClient(const QString &value)
{
    client = value;
}

void Client_Add_Car::on_txtPlain_Description_textChanged()
{
    Check_Car_Description_Size();
}

void Client_Add_Car::on_btn_Client_Add_Car_accepted()
{
    Add_Car(client);
}

void Client_Add_Car::on_btn_Client_Add_Car_rejected()
{
    close();
}
