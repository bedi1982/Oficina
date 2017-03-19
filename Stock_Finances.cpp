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
    query.prepare("SELECT SUM(Part_Cost), SUM(Part_Sell_Value_With_Interest_Rate) FROM Part");

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Finances::~Load_All()");
    }else{
        while(query.next()){
            ui->lcd_Stock_Total_Value_in_Cost->display(query.value(0).toString()); //Name
            ui->lcd_Stock_Total_Value_in_Sell->display(query.value(1).toString());
        }
    }

    query.prepare("SELECT sum(Part_Cost), SUM(Part_Sell_Value_With_Interest_Rate) FROM Part WHERE Part_created_at BETWEEN NOW() - INTERVAL 30 DAY AND NOW();");

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Finances::~Load_All()");
    }else{
        while(query.next()){
            ui->lcd_Stock_Total_Sold_Last_30->display(query.value(0).toString());
            double Part_Cost = query.value(0).toDouble();
            double Sell_Cost = query.value(1).toDouble();
            double diff = Part_Cost - Sell_Cost;
            ui->lcd_Profit_Last_30_Days->display(diff);
        }
    }

    query.prepare("SELECT sum(Part_Cost), SUM(Part_Sell_Value_With_Interest_Rate) FROM Part WHERE Part_created_at BETWEEN NOW() - INTERVAL 240 DAY AND NOW();");

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Finances::~Load_All()");
    }else{
        while(query.next()){
            ui->lcd_Stock_Total_Sold_Last_6_months->display(query.value(0).toString());
            double Part_Cost = query.value(0).toDouble();
            double Sell_Cost = query.value(1).toDouble();
            double diff = Part_Cost - Sell_Cost;
            ui->lcd_Profit_Last_240_Days->display(diff);
        }
    }

    query.prepare("SELECT sum(Part_Cost), SUM(Part_Sell_Value_With_Interest_Rate) FROM Part WHERE Part_created_at BETWEEN NOW() - INTERVAL 365 DAY AND NOW();");

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Finances::~Load_All()");
    }else{
        while(query.next()){
            ui->lcd_Stock_Total_Sold_Last_365->display(query.value(0).toString());
            double Part_Cost = query.value(0).toDouble();
            double Sell_Cost = query.value(1).toDouble();
            double diff = Part_Cost - Sell_Cost;
            ui->lcd_Profit_Last_365_Days->display(diff);
        }
    }
}

void Stock_Finances::on_buttonBox_rejected()
{
    close();
}
