#include "Client_Update.h"
#include "ui_Client_Update.h"

#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"

Client_Update::Client_Update(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Update)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

Client_Update::~Client_Update()
{
    delete ui;
}

QString Client_Update::getClient_id() const
{
    return client_id;
}

void Client_Update::setClient_id(const QString &value)
{
    client_id = value;
}

void Client_Update::load_Client_Info_To_TextBoxes()
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
            ui->line_Address->setText(query.value(2).toString()); //Adress
            ui->line_City->setText(query.value(3).toString()); //City
            ui->line_CPG->setText(query.value(4).toString()); //CPG
            ui->line_Personal_ID->setText(query.value(5).toString()); // Personal ID
            ui->line_Phone->setText(query.value(6).toString()); //Phone
            ui->line_Updated_At->setText(query.value(7).toString()); //updated At
            ui->line_Created_At->setText(query.value(8).toString()); //created At
        }
    }
}

void Client_Update::on_btn_Client_Update_accepted()
{
    QSqlQuery query;
    query.prepare(" UPDATE Client SET "
                  "  Client_Name = :Client_Name"
                  " ,Client_Address = :Client_Address"
                  " ,Client_City = :Client_City"
                  " ,Client_CPG = :Client_CPG"
                  " ,Client_ID_Number = :Client_ID_Number"
                  " ,Client_Phone = :Client_Phone"
                  " WHERE Client_id = " + client_id);

    query.bindValue(":Client_Name", ui->line_Name->text());
    query.bindValue(":Client_Address", ui->line_Address->text());
    query.bindValue(":Client_City", ui->line_City->text());
    query.bindValue(":Client_CPG", ui->line_CPG->text());
    query.bindValue(":Client_ID_Number", ui->line_Personal_ID->text());
    query.bindValue(":Client_Phone", ui->line_Phone->text());

    if (query.exec()) {
        QMessageBox::information(this, tr("Success"), tr("Client Updated!"));
        close();
    } else {
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "class Client_Edit::on_btn_update_clicked() ");
        close();
    }
}

void Client_Update::on_btn_Client_Update_rejected()
{
    close();
}
