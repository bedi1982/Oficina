#include "Employee_Add.h"
#include "ui_Employee_Add.h"
#include "qsqlquery.h"
#include "qmessagebox.h"
#include "QDebug"
#include "qsqlerror.h"

Employee_Add::Employee_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee_Add)
{
    ui->setupUi(this);
}

Employee_Add::~Employee_Add()
{
    delete ui;
}

void
    Employee_Add::Set_Emoticon()
{
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

bool
    Employee_Add::Verify_Empty_Fields_on_Form()
{
    if (   ui->line_Name->text() == ""
           ||ui->line_Address->text() == ""
           ||ui->line_City->text() == ""
           ||ui->line_Personal_ID->text() == ""
           ||ui->line_CPG->text() == ""
           ||ui->line_Phone->text() == ""
           )
    {
        ui->line_Name->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Employee_Add::Clear_Form(){
        ui->line_Name->setText("");
        ui->line_Address->setText("");
        ui->line_City->setText("");
        ui->line_Personal_ID->setText("");
        ui->line_CPG->setText("");
        ui->line_Phone->setText("");
        Set_Emoticon();
}

void Employee_Add::on_btn_Add_Client_accepted()
{
    if(Verify_Empty_Fields_on_Form()){
        QSqlQuery query;
        query.prepare("INSERT INTO"
                      " Employee (Employee_Name, Employee_Address, Employee_City, Employee_CPG, Employee_ID_Number, Employee_Phone)"
                      " VALUES (:Employee_Name, :Employee_Address, :Employee_City, :Employee_CPG, :Employee_ID_Number, :Employee_Phone)");

        query.bindValue(":Employee_Name", ui->line_Name->text());
        query.bindValue(":Employee_Address", ui->line_Address->text());
        query.bindValue(":Employee_City", ui->line_City->text());
        query.bindValue(":Employee_CPG", ui->line_CPG->text());
        query.bindValue(":Employee_ID_Number", ui->line_Personal_ID->text());
        query.bindValue(":Employee_Phone", ui->line_Phone->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". Class: addEmployee.cpp51");
        }else{
            QMessageBox::information(this, tr("IMPORTANT!"), ui->line_Name->text() + tr(" added. "
                                                                                      "It is very important that you take note "
                                                                                      "of your Employee ID, this one you need to "
                                                                                      "log into the system. "
                                                                                      "Your employee ID is %1").arg(query.lastInsertId().toInt()));
            Clear_Form();
        }
    }
}

void Employee_Add::on_btn_Add_Client_rejected()
{
    close();
}
