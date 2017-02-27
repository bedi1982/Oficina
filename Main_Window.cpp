#include "Main_Window.h"
#include "ui_Main_Window.h"

#include "Database.h"
#include "Client_Add.h"
#include "Client_Add_Service.h"
#include "Client_Services_History.h"
#include "Stock_Add_Part.h"
#include "Stock_Control.h"
#include "Stock_Finances.h"
#include "Config_Set_Hour_Cost.h"
#include "Man_Page.h"
#include "About.h"
#include "Employee_List.h"

#include "qsqlrelationaltablemodel.h"
#include "qsqlquery.h"
//#include "qdebug.h"
#include "qmessagebox.h"
#include "qsqlerror.h"
#include "Client_Services_History.h"
#include "System_Services_and_Info.h"

#include <qsortfilterproxymodel.h>

using namespace std;

Main_Window::Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_ID_or_CPG_or_Name->setFocus();
    ui->lbl_Database->setText("Database -> ");
    ui->lbl_Oficina->setText(System_Services_and_Info::get_System_Version());
    ui->lbl_Date->setText(System_Services_and_Info::get_Current_Date());
    this->setWindowTitle(System_Services_and_Info::get_System_Version());

    Database db;
    if(db.Connect()){
        QPixmap green(":/emoticons/emblem-default.png");
        ui->lbl_Emoticon_Connection_Status->setPixmap(green);
    }else{
        //If the database is not available we make it mostly useless//
        QPixmap red(":/emoticons/emblem-important.png");
        ui->lbl_Emoticon_Connection_Status->setPixmap(red);
        ui->line_ID_or_CPG_or_Name->setEnabled(false);
        ui->menuBar->hide();
    }
        System_Services_and_Info::Check_Text_Size(10);
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

    //We add the new Client in the search Result:
    QSqlQuery Get_last_Client;
    Get_last_Client.prepare("SELECT Client_id FROM Client ORDER BY Client_id DESC LIMIT 1;");

    if (Get_last_Client.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Get_last_Client.lastError().text() + "void Main_Window::on_action_Add_Client_triggered()");
    }else{
        while(Get_last_Client.next())
        {
            QString Last_client = Get_last_Client.value(0).toString();
            ui->line_ID_or_CPG_or_Name->setText(Last_client);
        }
    }
}

void Main_Window::on_action_Add_Part_triggered()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.setModal(true);
    Stock_Add_Part.exec();
}


void Main_Window::on_tbl_Client_List_doubleClicked(const QModelIndex &selectedClientinTheGrid)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant clientID = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
    QVariant clientCPG = model->data(model->index(selectedClientinTheGrid.row(), 4, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    Client_Services_Open(clientID.toString());

    //Going back to former form keeping current client 'searched' and updated
    //The empty String is to reset the 'on_text_changed' function.
    ui->line_ID_or_CPG_or_Name->setText("");
    ui->line_ID_or_CPG_or_Name->setText(clientCPG.toString());
}

void Main_Window::Client_Services_Open(QString clientID)
{
    Client_Services_History Client_Services_History;
    Client_Services_History.setClient_id(clientID);
    Client_Services_History.setModal(true);
    Client_Services_History.exec();
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

void Main_Window::on_line_ID_or_CPG_or_Name_textChanged(const QString &Used_Search_Filter)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(Used_Search_Filter.isEmpty()))
    {
        model->setTable("Client");
/*
        if(!(Used_Search_Filter == "*")){
            model->setFilter("Client_ID like '%" + Used_Search_Filter + "%'"
                            " OR Client_Name like '%" + Used_Search_Filter + "%'"
                            " OR Client_CPG like '%"  + Used_Search_Filter + "%'"
                            " OR Client_id like '%"   + Used_Search_Filter + "%'");
        }*/
        model->select();
        QSortFilterProxyModel proxy;
        proxy.setSourceModel(model);
        proxy.setFilterWildcard(Used_Search_Filter);

        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->setHeaderData(0, Qt::Horizontal, tr("System ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Adress"));
        model->setHeaderData(3, Qt::Horizontal, tr("City"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPG"));
        model->setHeaderData(5, Qt::Horizontal, tr("ID"));
        model->setHeaderData(6, Qt::Horizontal, tr("Phone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Updated at"));
        model->setHeaderData(8, Qt::Horizontal, tr("Created at"));

        ui->tbl_Client_List->setModel(model);
        ui->tbl_Client_List->hideColumn(2);
        ui->tbl_Client_List->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_Client_List->setModel(model);
        ui->tbl_Client_List->resizeColumnsToContents();
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

void Main_Window::on_Clear_Button_clicked()
{
        ui->line_ID_or_CPG_or_Name->setText("");
        ui->line_ID_or_CPG_or_Name->setFocus();
}

void Main_Window::on_actionStock_Finances_triggered()
{
    Stock_Finances Stock_Finances;
    Stock_Finances.setModal(true);
    Stock_Finances.exec();
}

void Main_Window::on_action_Employees_triggered()
{
    Employee_List Employee_List;
    Employee_List.setModal(true);
    Employee_List.exec();
}
