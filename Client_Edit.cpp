#include "Client_Edit.h"
#include "ui_Client_Edit.h"
#include "QDebug"
#include "QSqlQuery"
#include "QMessageBox"
#include "QSqlError"

Client_Edit::Client_Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Edit)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

Client_Edit::~Client_Edit()
{
    delete ui;
}

QString Client_Edit::getClient_id() const
{
    return client_id;
}

void Client_Edit::setClient_id(const QString &value)
{
    client_id = value;
}

void Client_Edit::loadClientInfo_to_TextBoxes()
{
    QSqlQuery query;
    query.prepare("SELECT * from Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class Client_Edit::loadClientInfo_to_TextBoxes() ");
    }else{
        while(query.next())
        {
            ui->line_ID->setText(query.value(0).toString()); //ID
            ui->line_Name->setText(query.value(1).toString()); //Name
            ui->line_Address->setText(query.value(2).toString()); //Adress
            ui->line_City->setText(query.value(3).toString()); //City
            ui->line_CPF->setText(query.value(4).toString()); //CPF
            ui->line_RG->setText(query.value(5).toString()); //RG
            ui->line_Phone->setText(query.value(6).toString()); //Phone
            ui->line_UpdatedAt->setText(query.value(7).toString()); //updated At
            ui->line_CreatedAt->setText(query.value(8).toString()); //created At
        }
    }
}

void Client_Edit::on_btn_update_clicked()
{
    QSqlQuery query;
    query.prepare(" UPDATE Client SET "
                              "  Client_Name = :Client_Name"
                              " ,Client_Address = :Client_Address"
                              " ,Client_City = :Client_City"
                              " ,Client_CPF = :Client_CPF"
                              " ,Client_RG = :Client_RG"
                              " ,Client_Phone = :Client_Phone"
                              " WHERE Client_id = " + client_id);

            query.bindValue(":Client_Name", ui->line_Name->text());
            query.bindValue(":Client_Address", ui->line_Address->text());
            query.bindValue(":Client_City", ui->line_City->text());
            query.bindValue(":Client_CPF", ui->line_CPF->text());
            query.bindValue(":Client_RG", ui->line_RG->text());
            query.bindValue(":Client_Phone", ui->line_Phone->text());

            if (query.exec()) {
                QMessageBox::information(this, tr("Sucesso"), tr("Cliente Atualizado!"));
                close();
            } else {
                QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class Client_Edit::on_btn_update_clicked() ");
                close();
            }
}
