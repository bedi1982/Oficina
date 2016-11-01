#include "addpart.h"
#include "ui_addpart.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"

addpart::addpart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addpart)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->doubleSpinCusto->setMaximum(9999);
}

addpart::~addpart()
{
    delete ui;
}

void addpart::limpaForm()
{
    ui->line_Nome->setText("");
    ui->line_Descricao->setText("");
    ui->doubleSpinCusto->clear();
    ui->spin_Quantidade->clear();
}

bool addpart::verificaCamposEmBrancoNoForm()
{
    if (   ui->line_Nome->text() == ""
           ||ui->line_Descricao->text() == ""
           ||ui->doubleSpinCusto->text() == ""
           ||ui->spin_Quantidade->text() == ""
       )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        limpaForm();
        ui->line_Nome->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addpart::on_btn_Sair_clicked()
{
    close();
}

void addpart::on_btn_Cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into Part (Part_Name, Part_Description, Part_Cost, Part_Quantity)"
                      "values (:Name, :Description, :Cost, :Quantity)");

        query.bindValue(":Name", ui->line_Nome->text());
        query.bindValue(":Description", ui->line_Descricao->text());
        query.bindValue(":Cost", ui->doubleSpinCusto->text().toDouble());
        query.bindValue(":Quantity", ui->spin_Quantidade->text().toInt());

        if (query.exec() == false){
            qDebug() << query.lastError();
        }
        ui->lbl_Feedback->setText(ui->line_Nome->text() + " adicionado ao estoque!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        ui->line_Nome->setFocus();
        limpaForm();
    }
}

