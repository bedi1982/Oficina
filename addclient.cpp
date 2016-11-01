#include "addclient.h"
#include "ui_addclient.h"
#include "mainwindow.h"
#include "QString"
#include "database.h"
#include "QtSql"

addclient::addclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addclient)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

addclient::~addclient()
{
    delete ui;
}

void addclient::limpaForm()
{
    ui->line_Nome->setText("");
    ui->line_Endereco->setText("");
    ui->line_Cidade->setText("");
    ui->line_RG->setText("");
    ui->line_CPF->setText("");
}

bool addclient::verificaCamposEmBrancoNoForm()
{
    if (   ui->line_Nome->text() == ""
           ||ui->line_Endereco->text() == ""
           ||ui->line_Cidade->text() == ""
           ||ui->line_RG->text() == ""
           ||ui->line_CPF->text() == ""
           )
    {
        ui->lbl_feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        limpaForm();
        ui->line_Nome->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addclient::on_btn_cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        //Start Database Operation//
        QSqlQuery query;
        query.prepare("insert into Client (Name, Address, City, CPF, RG)"
                      "values (:Name, :Address, :City, :CPF, :RG)");

        query.bindValue(":Name", ui->line_Nome->text());
        query.bindValue(":Address", ui->line_Endereco->text());
        query.bindValue(":City", ui->line_Cidade->text());
        query.bindValue(":CPF", ui->line_CPF->text());
        query.bindValue(":RG", ui->line_RG->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
        }

        ui->lbl_feedback->setText(ui->line_Nome->text() + " cadastrado!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        ui->line_Nome->setFocus();
        limpaForm();
    }
}
void addclient::on_btn_Sair_clicked()
{
    close();
}
