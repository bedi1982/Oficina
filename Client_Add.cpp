#include "Client_Add.h"
#include "ui_Client_Add.h"
#include "Main_Window.h"

#include "QString"
#include "Database.h"
#include "QtSql"
#include "QMessageBox"

Client_Add::Client_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->lbl_feedback->setText("Todos os campos devem estar preenchidos.");
}

Client_Add::~Client_Add()
{
    delete ui;
}

bool Client_Add::verificaCamposEmBrancoNoForm()
{
    if (   ui->line_Name->text() == ""
           ||ui->line_Address->text() == ""
           ||ui->line_City->text() == ""
           ||ui->line_RG->text() == ""
           ||ui->line_CPF->text() == ""
           ||ui->line_Phone->text() == ""
           )
    {
        ui->lbl_feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->line_Name->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Client_Add::on_btn_cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        //Start Database Operation//
        QSqlQuery query;
        query.prepare("insert into Client (Client_Name, Client_Address, Client_City, Client_CPF, Client_RG, Client_Phone)"
                      "values (:Name, :Address, :City, :CPF, :RG, :Phone)");

        query.bindValue(":Name", ui->line_Name->text());
        query.bindValue(":Address", ui->line_Address->text());
        query.bindValue(":City", ui->line_City->text());
        query.bindValue(":CPF", ui->line_CPF->text());
        query.bindValue(":RG", ui->line_RG->text());
        query.bindValue(":Phone", ui->line_Phone->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, "Erro!", query.lastError().text() + ". Class: addclient.cpp51");
        }else{
            ui->lbl_feedback->setText(ui->line_Name->text() + " cadastrado!");
            QPixmap cool(":/emoticons/face-cool.png");
            ui->lbl_Emoticon->setPixmap(cool);
            QMessageBox::information(this, "Sucesso!", "Cliente adicionado.");
            close();
        }
    }
}
void Client_Add::on_btn_Sair_clicked()
{
    close();
}
