#include "editclient.h"
#include "ui_editclient.h"
#include "QSqlTableModel"
#include "QDebug"

EditClient::EditClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditClient)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

EditClient::~EditClient()
{
    delete ui;
}

void EditClient::LoadEditableGrid(QString ClientID)
{
        QSqlTableModel* model = new QSqlTableModel;
        model->setTable("Client");
        model->setFilter("Client_id = " + ClientID);
        model->select();
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        model->setHeaderData(2, Qt::Horizontal, tr("Endereço"));
        model->setHeaderData(3, Qt::Horizontal, tr("Cidade"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPF"));
        model->setHeaderData(5, Qt::Horizontal, tr("RG"));
        model->setHeaderData(6, Qt::Horizontal, tr("Telefone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Atualizado em"));
        model->setHeaderData(8, Qt::Horizontal, tr("Cliente desde"));

        ui->tbl_EditClient->setColumnWidth(1, 40);
        ui->tbl_EditClient->setColumnWidth(2, 50);
        ui->tbl_EditClient->setColumnWidth(3, 30);
        ui->tbl_EditClient->setColumnWidth(4, 20);
        ui->tbl_EditClient->setColumnWidth(5, 15);
        ui->tbl_EditClient->setColumnWidth(6, 40);

        ui->tbl_EditClient->setModel(model);
        ui->tbl_EditClient->hideColumn(0);
        ui->tbl_EditClient->hideColumn(7);
        ui->tbl_EditClient->hideColumn(8);
        ui->tbl_EditClient->resizeColumnsToContents();
}

void EditClient::on_btn_sair_clicked()
{
    close();
}
