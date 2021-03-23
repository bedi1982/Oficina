#include "Database.h"
#include "QtSql"
#include "QMessageBox"
#include "QStackedWidget"
#include "QSqlQuery"

#include "Client_Add.h"
#include "ui_Client_Add.h"
#include "System_Services_and_Info.h"
#include "QMainWindow"
#include "Main_Window.h"

#include "QSettings"

Client_Add::Client_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add)
{
    ui->setupUi(this);
    Set_Emoticon();
    ui->line_Name->setFocus();
    LoadSettings();
}

Client_Add::~Client_Add()
{
    SaveSettings();
    delete ui;
}

void Client_Add::Set_Emoticon()
{
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

bool Client_Add::Verify_Empty_Fields_on_Form()
{
    if (   ui->line_Name->text() == ""
           ||ui->line_Address->text() == ""
           ||ui->line_City->text() == ""
           ||ui->line_Personal_ID->text() == ""
           ||ui->line_Phone->text() == ""
           )
    {
        ui->lbl_feedback->setText(tr("All fields need to be filled!"));
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->line_Name->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Client_Add::Clear_Form(){
        ui->line_Name->setText("");
        ui->line_Address->setText("");
        ui->line_City->setText("");
        ui->line_Personal_ID->setText("");
        ui->line_Phone->setText("");
        ui->lbl_feedback->setText("");
        Set_Emoticon();
}

void Client_Add::on_btn_Add_Client_accepted()
{
    if(Verify_Empty_Fields_on_Form()){

        QSqlQuery query;
        query.prepare("INSERT INTO"
                      " Client (Client_Name, Client_Address, Client_City, Client_ID_Number, Client_Phone)"
                      " VALUES (:Client_Name, :Client_Address, :Client_City, :Client_ID_Number, :Client_Phone)");

        query.bindValue(":Client_Name", ui->line_Name->text());
        query.bindValue(":Client_Address", ui->line_Address->text());
        query.bindValue(":Client_City", ui->line_City->text());
        query.bindValue(":Client_ID_Number", ui->line_Personal_ID->text());
        query.bindValue(":Client_Phone", ui->line_Phone->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". Class: addclient.cpp");
        }else{
            ui->lbl_feedback->setText(ui->line_Name->text() + tr(" added!"));
            QPixmap cool(":/emoticons/face-cool.png");
            ui->lbl_Emoticon->setPixmap(cool);
            QMessageBox::information(this, tr("Success!"), ui->line_Name->text() + tr(" added"));

            //this one is because if the user presses ESC he actually isn't adding a new client, the main window needs to know that//
            //otherwise it will display the last client from the database//
            close();
        }
    }
}

void Client_Add::on_btn_Add_Client_rejected()
{
    close();
}

//Block to keep windows position and size//

void Client_Add::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Add");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}

void Client_Add::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Client_Add");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}
//End block to keep windows position and size//
