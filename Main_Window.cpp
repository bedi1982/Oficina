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
#include "Client_Services_History.h"
#include "System_Services_and_Info.h"
#include "QSettings"

#include "qsqlquery.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "qsqlerror.h"
#include "Login.h"

#include <qsortfilterproxymodel.h>

using namespace std;

Main_Window::~Main_Window()
{
    delete ui;
}

Main_Window::Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //window size
    LoadSettings();
    //end window size

    //TODO TEST
    ui->line_ID_or_CPG_or_Name->setFocus();
    ui->lbl_Oficina->setText(System_Services_and_Info::get_System_Version() + "\n" + System_Services_and_Info::get_Current_Date());
    this->setWindowTitle(System_Services_and_Info::get_System_Version());

    Database db;

    if(db.Connect()){
        Check_Login();
        ui->lbl_Database->setText(tr("Database:  Connected"));
        Create_Client_Model_and_proxy();

        //We also check if the hourcost is set, otherwise is to dangerous the user may start a service with hour cost at 0;
        if(!get_Last_Hour_Cost()){
            QMessageBox::critical(this, tr("First Run WARNING!!"), "Working Hour Cost is not set!!\n"
                                                         "Please set an HourCost in: Configuration -> Change HourCost.\n"
                                                         "\nNot setting this value will make you work for FREE!");
        }
    }else{
        //If the database is not available we make it mostly useless//
        ui->line_ID_or_CPG_or_Name->setEnabled(false);
        ui->menuBar->hide();
        ui->lbl_Database->setText(tr("Database:  Disconnected"));
    }
}

bool Main_Window::get_Last_Hour_Cost()
{
    QSqlQuery Get_Hour_Cost;
    Get_Hour_Cost.prepare("SELECT * from HourCost order by HourCost_id DESC LIMIT 1;");

    if (Get_Hour_Cost.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Get_Hour_Cost.lastError().text() + "bool Main_Window::get_Last_Hour_Cost()");
    }else{
        while(Get_Hour_Cost.next()) //returns only 1 row as result(0 = id, 1=name)//
        {
            if (Get_Hour_Cost.value(1).toInt() > 0){
                return true;
            }
        }
    }
    return false;
}

bool Main_Window::getClient_Clicked_Exit_On_Login() const
{
    return Client_Clicked_Exit_On_Login;
}

void Main_Window::setClient_Clicked_Exit_On_Login(bool value)
{
    Client_Clicked_Exit_On_Login = value;
}

void Main_Window::Check_Login()
{
    Login Login;
    Login.exec();
}

void Main_Window::Set_Last_Client_in_the_Grid()
{
    QSqlQuery Get_last_Client;
    Get_last_Client.prepare("SELECT Client_id, Client_Name FROM Client ORDER BY Client_id DESC LIMIT 1;");

    if (Get_last_Client.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Get_last_Client.lastError().text() + "void Main_Window::on_action_Add_Client_triggered()");
    }else{
        while(Get_last_Client.next()) //returns only 1 row as result(0 = id, 1=name)//
        {
            ui->line_ID_or_CPG_or_Name->setText(Get_last_Client.value(1).toString()); //put the retrieved name in the search bar so it get automatically 'searched'
        }
    }
}

void Main_Window::on_action_Add_Client_triggered()
{
    Client_Add Client_Add;
    Client_Add.exec();

    if(System_Services_and_Info::get_is_New_or_Updated_Client()){
        Create_Client_Model_and_proxy();
        Set_Last_Client_in_the_Grid();
    }
    System_Services_and_Info::set_is_New_or_Updated_Client(false);
}

void Main_Window::on_action_Add_Part_triggered()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.exec();
}

void Main_Window::on_tbl_Client_List_doubleClicked(const QModelIndex &selectedClientinTheGrid)
{
    //Bellow 2 list will retrieve the column 0 value, which is the clientid//
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant clientID = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
    QVariant clientName = model->data(model->index(selectedClientinTheGrid.row(), 1, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    Client_Services_Open(clientID.toString());

    //Going back to former form keeping current client 'searched' and updated
    //The empty String is to reset the 'on_text_changed' function.
    ui->line_ID_or_CPG_or_Name->setText("");
    ui->line_ID_or_CPG_or_Name->setText(clientName.toString());
}

void Main_Window::Client_Services_Open(QString clientID)
{
    Client_Services_History Client_Services_History;
    Client_Services_History.setClient_id(clientID);
    Client_Services_History.exec();
}

void Main_Window::Create_Client_Model_and_proxy(){

    model = new QSqlTableModel();
    model->setTable("Client");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Adress"));
    model->setHeaderData(3, Qt::Horizontal, tr("City"));
    model->setHeaderData(4, Qt::Horizontal, tr("CPG"));
    model->setHeaderData(5, Qt::Horizontal, tr("ID"));
    model->setHeaderData(6, Qt::Horizontal, tr("Phone"));
    model->setHeaderData(7, Qt::Horizontal, tr("Updated at"));
    model->setHeaderData(8, Qt::Horizontal, tr("Created at"));

    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(model);
    proxy->setFilterKeyColumn(1);//Name
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->tbl_Client_List->setModel(proxy);
    ui->tbl_Client_List->setColumnHidden(2, true);
    ui->tbl_Client_List->resizeColumnsToContents();
}

void Main_Window::on_line_ID_or_CPG_or_Name_textChanged(const QString &Used_Search_Filter)
{
    proxy->setFilterFixedString(Used_Search_Filter);
}

void Main_Window::on_action_Stock_triggered()
{
    Stock_Control stock_Control;
    stock_Control.exec();
}

void Main_Window::on_action_Change_Hour_Cost_triggered()
{
    Config_Set_Hour_Cost set_Hour_Cost;
    set_Hour_Cost.exec();
}

void Main_Window::on_action_Manpage_triggered()
{
    Man_Page man_page;
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
    Stock_Finances.exec();
}

void Main_Window::on_action_Exit_triggered()
{
    SaveSettings();
    close();
}

void Main_Window::on_action_About_Oficina_triggered()
{
    About About;
    About.exec();
}

//Settings: Block to keep windows position and size//
void Main_Window::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Main_Window");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}

void Main_Window::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Main_Window");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}
//End block to keep windows position and size//
