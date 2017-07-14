#include "Stock_Update_Part.h"
#include "ui_Stock_Update_Part.h"
#include "System_Services_and_Info.h"

#include <qsqlquery.h>
#include <qdebug.h>
#include "qmessagebox.h"
#include "qsqlerror.h"

Stock_Update_Part::Stock_Update_Part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Update_Part)
{
    ui->setupUi(this);
}

QString Stock_Update_Part::getPartID() const
{
    return partID;
}

void Stock_Update_Part::setPartID(const QString &value)
{
    partID = value;
}

Stock_Update_Part::~Stock_Update_Part()
{
    delete ui;
}

void Stock_Update_Part::Load_Part_Info_to_Form(){
    QSqlQuery query;
    query.prepare("SELECT Part_id, Part_Name, Part_Brand, Part_Description, Part_Cost, Part_Sell_Value_With_Interest_Rate, Part_Quantity, Part_Interrest_Rate FROM Part WHERE Part_id = " + partID);

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Update_Part::Load_Part_Info_to_Form()");
    }else{
        while(query.next())
        {
            ui->line_Part_id->setText(query.value(0).toString());
            ui->line_Name->setText(query.value(1).toString());
            ui->line_Brand->setText(query.value(2).toString());
            ui->txt_Part_Description->setPlainText(query.value(3).toString());
            ui->double_Spin_Cost_Price->setValue(query.value(4).toDouble());
            ui->line_Final_Sell_Price->setText(query.value(5).toString());
            ui->spin_Quantity->setValue(query.value(6).toInt());
            ui->double_Spin_Interrest_Rate->setValue(query.value(7).toDouble());
        }
    }
}

void Stock_Update_Part::on_buttonBox_accepted()
{
    QSqlQuery Update_Part;
    Update_Part.prepare("UPDATE Part SET"
                        " Part_Name = :Part_Name,"
                        " Part_Brand = :Part_Brand,"
                        " Part_Description = :Part_Description,"
                        " Part_Cost = :Part_Cost,"
                        " Part_Sell_Value_With_Interest_Rate = :Part_Sell_Value_With_Interest_Rate,"
                        " Part_Quantity = :Part_Quantity,"
                        " Part_Interrest_Rate = :Part_Interrest_Rate"
                        " WHERE Part_id = :Part_id");

    Update_Part.bindValue(":Part_Name", ui->line_Name->text());
    Update_Part.bindValue(":Part_Brand", ui->line_Brand->text());
    Update_Part.bindValue(":Part_Description", ui->txt_Part_Description->toPlainText());
    Update_Part.bindValue(":Part_Cost", ui->double_Spin_Cost_Price->value());
    Update_Part.bindValue(":Part_Quantity", ui->spin_Quantity->value());
    Update_Part.bindValue(":Part_Interrest_Rate", ui->double_Spin_Interrest_Rate->value());

    double Price_With_Interrest = ui->double_Spin_Cost_Price->value() * ui->double_Spin_Interrest_Rate->value() / 100 + ui->double_Spin_Cost_Price->value();
    Update_Part.bindValue(":Part_Sell_Value_With_Interest_Rate", Price_With_Interrest);

    Update_Part.bindValue(":Part_id", ui->line_Part_id->text().toInt());

    if (!(Update_Part.exec())){
        QMessageBox::critical(this, tr("Error!"), Update_Part.lastError().text() + "class Stock_Control::on_btn_save_clicked()");
    }else{
        QMessageBox::information(this, tr("Success!"), tr("Part Updated."));
    }
    close();
}

void Stock_Update_Part::on_txt_Part_Description_textChanged()//Check for bigger description then allowed 250//
{

    const int max_size = 250;

    if(ui->txt_Part_Description->toPlainText().length() > max_size){;
        ui->txt_Part_Description->setPlainText(System_Services_and_Info::Check_Text_Size(max_size, ui->txt_Part_Description->toPlainText()));

        //Warn the user:
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the text shorter then %1 chars.").arg(max_size));

        //Put cursor back to the end of the text//
        QTextCursor cursor = ui->txt_Part_Description->textCursor();
        cursor.setPosition(ui->txt_Part_Description->document()->characterCount() - 1);
        ui->txt_Part_Description->setTextCursor(cursor);
    }
}

void Stock_Update_Part::on_buttonBox_rejected()
{
    close();
}
