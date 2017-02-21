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

#include "QSqlRelationalTableModel"
#include "QSqlQuery"
#include "QDebug"

using namespace std;

Main_Window::Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_ID_or_CPF_or_Name->setFocus();
    ui->lbl_Database->setText("Database -> ");

    Database db;
    if(db.Connect()){
        QPixmap green(":/emoticons/emblem-default.png");
        ui->lbl_Emoticon_Connection_Status->setPixmap(green);
    }else{
        //If the database is not available we make it mostly useless//
        QPixmap red(":/emoticons/emblem-important.png");
        ui->lbl_Emoticon_Connection_Status->setPixmap(red);
        ui->line_ID_or_CPF_or_Name->setEnabled(false);
        ui->menuBar->hide();
    }
}

Main_Window::~Main_Window()
{
    delete ui;
}

void Main_Window::on_action_Add_Client_triggered()
{
    Client_Add Client_Add;
    Client_Add.setModal(true);
    Client_Add.exec();
}

void Main_Window::on_action_Add_Part_triggered()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.setModal(true);
    Stock_Add_Part.exec();
}

void Main_Window::on_tbl_Services_History_doubleClicked(const QModelIndex &selectedClientinTheGrid)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant clientID = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
    QVariant clientCPF = model->data(model->index(selectedClientinTheGrid.row(), 4, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    Client_Services_History client_Services_History;
    client_Services_History.setClient_id(clientID.toString());
    client_Services_History.loadAll();
    client_Services_History.setModal(true);
    client_Services_History.exec();

    //Going back to former form keeping current client 'searched' and updated
    //The empty String is to reset the 'on_text_changed' function.
    ui->line_ID_or_CPF_or_Name->setText("");
    ui->line_ID_or_CPF_or_Name->setText(clientCPF.toString());
}

void Main_Window::on_action_Exit_triggered()
{
    close();
}

void Main_Window::on_action_About_Oficina_triggered()
{
    About About;
    About.setModal(true);
    About.exec();
}

void Main_Window::on_line_ID_or_CPF_or_Name_textChanged(const QString &userSearchFilter)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(userSearchFilter.isEmpty()))
    {
        model->setTable("Client");
        if(!(userSearchFilter == "*")){
            model->setFilter("Client_RG like '%" + userSearchFilter + "%'"
                            " OR Client_Name like '%" + userSearchFilter + "%'"
                            " OR Client_CPF like '%"  + userSearchFilter + "%'"
                            " OR Client_id like '%"   + userSearchFilter + "%'");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setHeaderData(0, Qt::Horizontal, tr("System ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Adress"));
        model->setHeaderData(3, Qt::Horizontal, tr("City"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPF"));
        model->setHeaderData(5, Qt::Horizontal, tr("ID"));
        model->setHeaderData(6, Qt::Horizontal, tr("Phone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Updated at"));
        model->setHeaderData(8, Qt::Horizontal, tr("Created at"));

        ui->tbl_Services_History->setModel(model);
        ui->tbl_Services_History->hideColumn(2);
        ui->tbl_Services_History->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_Services_History->setModel(model);
        ui->tbl_Services_History->resizeColumnsToContents();
    }
}

void Main_Window::on_action_Stock_triggered()
{
    Stock_Control stock_Control;
    stock_Control.setModal(true);
    stock_Control.exec();
}

void Main_Window::on_action_Change_Hour_Cost_triggered()
{
    Config_Set_Hour_Cost set_Hour_Cost;
    set_Hour_Cost.setModal(true);
    set_Hour_Cost.exec();
}

void Main_Window::on_action_Manpage_triggered()
{
    Man_Page man_page;
    man_page.setModal(true);
    man_page.exec();
}

void Main_Window::on_pushButton_clicked()
{
        ui->line_ID_or_CPF_or_Name->setText("");
}
