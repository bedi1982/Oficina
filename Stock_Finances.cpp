#include "Stock_Finances.h"
#include "ui_Stock_Finances.h"

#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qmessagebox.h"
#include "qdebug.h"

Stock_Finances::Stock_Finances(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Finances)
{
    ui->setupUi(this);
    Load_All();
}

Stock_Finances::~Stock_Finances()
{
    delete ui;
}

void Stock_Finances::Load_All(){
    QSqlQuery query;
    query.prepare("SELECT SUM(Part_Cost) FROM Part");

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Finances::~Load_All()");
    }else{
        while(query.next()){
            ui->lcd_Stock_Total_Value_in_Cost->display(query.value(0).toString()); //Name
        }
    }
}
