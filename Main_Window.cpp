#include "Main_Window.h"
#include "ui_Main_Window.h"
#include "Database.h"
#include "Client_Add.h"
#include "Stock_Add_Part.h"
#include "Client_Add_Service.h"
#include "Client_Services_History.h"
#include "About.h"
#include "Stock_Control.h"
#include "Config_Set_Hour_Cost.h"
#include "Man_Page.h"

#include <QSqlTableModel>
#include "QSqlRelationalTableModel"
#include "QSqlQuery"
#include "QMessageBox"

#include "QDebug"

using namespace std;

Main_Window::Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_RGouCPFouNome->setFocus();

    QPixmap sportCar(":/emoticons/sport-car.png");
    ui->lbl_BigCarIcon->setPixmap(sportCar);


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

Main_Window::~Main_Window()
{
    delete ui;
}

void Main_Window::on_actionAddCliente_triggered()
{
    Client_Add Client_Add;
    Client_Add.setModal(true);
    Client_Add.exec();
}

void Main_Window::on_actionAddPeca_triggered()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.setModal(true);
    Stock_Add_Part.exec();
}

void Main_Window::on_tbl_historicoServicos_doubleClicked(const QModelIndex &selectedClientinTheGrid)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant clientID = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    Client_Services_History client_Services_History;
    client_Services_History.setClient_id(clientID.toString());
    client_Services_History.loadAll();
    client_Services_History.setModal(true);
    client_Services_History.exec();
    ui->line_RGouCPFouNome->setText(clientID.toString());
}

void Main_Window::on_actionSair_triggered()
{
    close();
}

void Main_Window::on_actionSobreOficina_triggered()
{
    About About;
    About.setModal(true);
    About.exec();
}

void Main_Window::on_line_RGouCPFouNome_textChanged(const QString &userSearchFilter)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(userSearchFilter.isEmpty()))
    {
        model->setTable("Client");
        if(!(userSearchFilter == "*"))
        {
            model->setFilter(" Client_RG like '%" + userSearchFilter + "%' "
                             "OR Client_Name like '%" + userSearchFilter + "%' "
                             "OR Client_CPF like '%" + userSearchFilter + "%' "
                             "OR Client_id like '%" + userSearchFilter + "%' ");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        model->setHeaderData(2, Qt::Horizontal, tr("Endereço"));
        model->setHeaderData(3, Qt::Horizontal, tr("Cidade"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPF"));
        model->setHeaderData(5, Qt::Horizontal, tr("RG"));
        model->setHeaderData(6, Qt::Horizontal, tr("Telefone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Atualizado em"));
        model->setHeaderData(8, Qt::Horizontal, tr("Criado em"));

        ui->tbl_historicoServicos->setModel(model);
        ui->tbl_historicoServicos->hideColumn(2);
        ui->tbl_historicoServicos->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_historicoServicos->setModel(model);
        ui->tbl_historicoServicos->resizeColumnsToContents();
    }
}

void Main_Window::on_actionEstoque_triggered()
{
    Stock_Control stock_Control;
    stock_Control.setModal(true);
    stock_Control.exec();
}

void Main_Window::on_actionAlterar_Custo_da_Hora_triggered()
{
    Config_Set_Hour_Cost set_Hour_Cost;
    set_Hour_Cost.setModal(true);
    set_Hour_Cost.exec();
}

void Main_Window::on_actionManual_do_usu_rio_triggered()
{
    Man_Page man_page;
    man_page.setModal(true);
    man_page.exec();
}
