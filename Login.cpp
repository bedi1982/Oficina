#include "Login.h"
#include "ui_Login.h"

#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "System_Services_and_Info.h"
#include "QIntValidator"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->line_ID->setPlaceholderText("Only Numbers Allowed");
    ui->line_ID->setValidator(new QIntValidator);
}

Login::~Login()
{
    delete ui;
}

bool Login::Verify_Empty_Fields_on_Form()
{
    if(ui->line_ID->text() == "" || ui->line_Password->text() == ""){
        ui->label_Feedback->setText(tr("All fields need to be filled!"));
        ui->line_ID->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

//Employee part totally disabled
void Login::on_buttonBox_accepted()
{/*
    if(Verify_Empty_Fields_on_Form()){
        QString Employee_Id = ui->line_ID->text();
        QString Employee_Password = ui->line_Password->text();

        QSqlQuery query;
        query.prepare("SELECT Employee_id, Employee_Password FROM Employee WHERE Employee_id = " + Employee_Id);

        if (query.exec() == false){
            QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "class void Login::on_buttonBox_accepted()");
        }else{
            while(query.next())
            {
                if((query.value(1) == Employee_Password)  || (Employee_Id == "1" && Employee_Password == "1") ){
                    //We store the logged func for use later//
                    System_Services_and_Info::set_Logged_func(Employee_Id.toInt());
                    qDebug() << "Matched, an user logs in";
                    hide();
                }else{
                    ui->label_Feedback->setText("Failed Login");
                }
            }
        }
    }*/
    hide();
}

void Login::on_buttonBox_rejected()
{
    exit(0);
}
