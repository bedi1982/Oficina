#include "Partgroup_Add.h"
#include "ui_Partgroup_Add.h"

#include "qsqlquery.h"
#include "qsqlerror.h"

#include "qmessagebox.h"
#include "QDebug"

PartGroup_Add::PartGroup_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PartGroup_Add)
{
    ui->setupUi(this);
}

PartGroup_Add::~PartGroup_Add()
{
    delete ui;
}


void PartGroup_Add::on_btn_Save_clicked()
{
    QSqlQuery PartGroup_Add;

    PartGroup_Add.prepare("INSERT INTO PartGroup (PartGroup_Name, PartGroup_Description) VALUES (:PartGroup_Name, :PartGroup_Description)");
    PartGroup_Add.bindValue(":PartGroup_Name", ui->line_PartGroupName->text());
    PartGroup_Add.bindValue(":PartGroup_Description", ui->line_PartGroup_Description->text());


    if (PartGroup_Add.exec() == false){
        qDebug() << PartGroup_Add.lastError();
        QMessageBox::critical(this, tr("Error!"), PartGroup_Add.lastError().text() + "Class: PartGroup_Add:30");
    }else{
        QMessageBox::information(this, tr("Success!"), ui->line_PartGroupName->text() + tr(" added"));
        close();
    }
}
