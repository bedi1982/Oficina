#include "addservice.h"
#include "ui_addservice.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "mainwindow.h"

int clientid;
QString clientname;

addservice::addservice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addservice)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

addservice::~addservice()
{
    delete ui;
}

void addservice::limpaForm()
{
    ui->line_ShortDescription->setText("");
    ui->txt_FullDescription->setText("");
}

bool addservice::verificaCamposEmBrancoNoForm()
{
    if (ui->txt_FullDescription->toPlainText() == ""
      ||ui->line_ShortDescription->text() == ""
           )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        limpaForm();
        ui->line_ShortDescription->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addservice::on_btn_Cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into Service (Service_Client_id, Service_Short_Description, Service_Description, Service_Cost)"
                      "values (:Service_Client_id, :Service_Short_Description, :Service_Description, :Service_Cost)");
        clientid = 5    ;
        query.bindValue(":Service_Client_id", clientid);
        query.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());
        query.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());
        query.bindValue(":Service_Cost", ui->doubleSpinCusto->text().toDouble());

        if (query.exec() == false){
            qDebug() << query.lastError();
        }
        ui->lbl_Feedback->setText("Serviço adicionado!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        ui->line_ShortDescription->setFocus();
        limpaForm();
    }
}

void addservice::setClientIdandName(int id, QString name)
{
    clientid = id;
    clientname = name;
    QString clientId = QString::number(id);
    qDebug() << clientId;
    ui->lbl_Feedback->setText("Adicionando serviço para " + clientname + ". Cadastro N: " + clientId);
}

void addservice::on_btn_Sair_clicked()
{
    close();
}
