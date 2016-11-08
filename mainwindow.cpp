#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "addclient.h"
#include "addpart.h"
#include "addservice.h"
#include "clientinfo.h"
#include "about.h"

#include <QSqlTableModel>
#include "QSqlRelationalTableModel"
#include "QSqlQuery"
#include "QMessageBox"

#include "QDebug"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap tux(":/emoticons/tux.png");
    ui->lbl_AppIcon->setPixmap(tux);
    ui->line_RGouCPFouNome->setFocus();

    Database db;
    if(db.conectar()){
        QPixmap green(":/emoticons/emblem-default.png");
        ui->lbl_emoticonStatusConexao->setPixmap(green);
        ui->lbl_bancodeDados->setText("Banco de dados: UP");
    }else{
        QPixmap red(":/emoticons/emblem-important.png");
        ui->lbl_emoticonStatusConexao->setPixmap(red);
        ui->lbl_bancodeDados->setText("Banco de dados: OFF ");
        ui->line_RGouCPFouNome->setEnabled(false);
        ui->menuBar->hide();
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

void MainWindow::on_tbl_historicoServicos_doubleClicked(const QModelIndex &selectedClientinTheGrid)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant clientID = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);

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

    if(!(userSearchFfilter.isEmpty()))
    {
        model->setTable("Client");
        if(!(userSearchFfilter == "*"))
        {
            model->setFilter(" Client_CPF like '%" + userSearchFfilter + "%' OR Client_Name like '%" + userSearchFfilter + "%' OR Client_RG like '%" + userSearchFfilter + "%'");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        //model->removeColumn(0); //ID
        model->removeColumn(6); //ID
        //model->removeColumn(9); //ID
        //model->setHeaderData(0, Qt::Horizontal, tr("Id"));
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        model->setHeaderData(2, Qt::Horizontal, tr("Endereço"));
        model->setHeaderData(3, Qt::Horizontal, tr("Cidade"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPF"));
        model->setHeaderData(5, Qt::Horizontal, tr("RG"));
        model->setHeaderData(6, Qt::Horizontal, tr("Telefone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Cliente desde"));

        //xnx to make columns ajust to cell content//
        //tip from here: http://stackoverflow.com/questions/3433664/how-to-make-sure-columns-in-qtableview-are-resized-to-the-maximum//
        ui->tbl_historicoServicos->setVisible(false);
        ui->tbl_historicoServicos->resizeColumnsToContents();
        ui->tbl_historicoServicos->setVisible(true);

        //ui->tbl_historicoServicos->resizeRowsToContents();
        ui->tbl_historicoServicos->setModel(model);
    }else{
        model->clear();

        ui->tbl_historicoServicos->setModel(model);
    }
}
