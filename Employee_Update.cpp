#include "Employee_Update.h"
#include "ui_Employee_Update.h"
#include "qsqlquery.h"
#include "qmessagebox.h"
#include "QDebug"
#include "qsqlerror.h"

Employee_Update::Employee_Update(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee_Update)
{
    ui->setupUi(this);
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
}

Employee_Update::~Employee_Update()
{
    delete ui;
}

QString Employee_Update::getEmployee_id() const
{
    return employee_id;
}

void Employee_Update::setEmployee_id(const QString &value)
{
    employee_id = value;
}

void Employee_Update::load_Employee_Info_To_TextBoxes()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Employee WHERE Employee_id = " + employee_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + "void Employee_Update::load_Employee_Info_To_TextBoxes()");
    }else{
        while(query.next())
        {
            ui->line_SysID->setText(query.value(0).toString()); //SystemID
            ui->line_Name->setText(query.value(1).toString()); //Name
            ui->line_Address->setText(query.value(2).toString()); //Adress
            ui->line_City->setText(query.value(3).toString()); //City
            ui->line_CPG->setText(query.value(4).toString()); //CPG
            ui->line_Personal_ID->setText(query.value(5).toString()); // Personal ID
            ui->line_Phone->setText(query.value(6).toString()); //Phone
            ui->line_Updated_At->setText(query.value(7).toString()); //updated At
            ui->line_Created_At->setText(query.value(8).toString()); //created At
        }
    }
}

void Employee_Update::on_btn_Employee_Update_accepted()
{
    QSqlQuery query;
    query.prepare(" UPDATE Employee SET "
                  "  Employee_Name = :Employee_Name"
                  " ,Employee_Address = :Employee_Address"
                  " ,Employee_City = :Employee_City"
                  " ,Employee_CPG = :Employee_CPG"
                  " ,Employee_ID_Number = :Employee_ID_Number"
                  " ,Employee_Phone = :Employee_Phone"
                  " WHERE Employee_id = " + employee_id);

    query.bindValue(":Employee_Name", ui->line_Name->text());
    query.bindValue(":Employee_Address", ui->line_Address->text());
    query.bindValue(":Employee_City", ui->line_City->text());
    query.bindValue(":Employee_CPG", ui->line_CPG->text());
    query.bindValue(":Employee_ID_Number", ui->line_Personal_ID->text());
    query.bindValue(":Employee_Phone", ui->line_Phone->text());

    if (query.exec()) {
        QMessageBox::information(this, tr("Success"), tr("Employee Updated!"));
        close();
    } else {
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + "void Employee_Update::on_btn_Employee_Update_accepted()");
        close();
    }
}
