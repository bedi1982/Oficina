#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "addclient.h"
#include "addpart.h"
#include "addservice.h"
#include "about.h"
#include <QSqlTableModel>
#include "QDebug"
#include "QSqlRelationalTableModel"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "clientinfo.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->line_RGouCPFouNome->setFocus();

    Database db;
    if(db.conectar()){
        QPixmap wink(":/emoticons/face-wink.png");
        ui->lbl_emoticonStatusConexao->setPixmap(wink);
        ui->lbl_bancodeDados->setText("Banco de dados: UP");
    }else{
        QPixmap sick(":/emoticons/face-sick.png");
        ui->lbl_emoticonStatusConexao->setPixmap(sick);
        ui->lbl_bancodeDados->setText("Banco de dados: DOWN");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAddCliente_triggered()
{
    addclient addclient;
    addclient.setModal(true);
    addclient.exec();
}

void MainWindow::on_actionAddPeca_triggered()
{
    addpart addpart;
    addpart.setModal(true);
    addpart.exec();
}

/*
void MainWindow::on_btn_procurarClientes_clicked()
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Client");
    model->setFilter(" Client_CPF like '%" + ui->line_RGouCPFouNome->text() + "%' OR Client_Name like '%" + ui->line_RGouCPFouNome->text() + "%' OR Client_RG like '%" + ui->line_RGouCPFouNome->text() + "%'");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tbl_historicoServicos->setModel(model);
}
*/

void MainWindow::on_tbl_historicoServicos_doubleClicked(const QModelIndex &index)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = index.model();
    QVariant clientID = model->data(model->index(index.row(), 0, index.parent()), Qt::DisplayRole);

    clientinfo clientinfo;
    clientinfo.setClient_Id(clientID.toString());
    clientinfo.loadAll();
    clientinfo.setModal(true);
    clientinfo.exec();
}

void MainWindow::on_actionSair_triggered()
{
    close();
}

void MainWindow::on_actionSobreOficina_triggered()
{
    about about;
    about.setModal(true);
    about.exec();
}

void MainWindow::on_line_RGouCPFouNome_textChanged(const QString &userSearchFfilter)
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("Client");
    model->setFilter(" Client_CPF like '%" + userSearchFfilter + "%' OR Client_Name like '%" + userSearchFfilter + "%' OR Client_RG like '%" + userSearchFfilter + "%'");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tbl_historicoServicos->setModel(model);
}
