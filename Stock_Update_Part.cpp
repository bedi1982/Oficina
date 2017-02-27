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
    query.prepare("SELECT Part_Name, Part_Description, Part_Cost, Part_Sell_Price, Part_Quantity, Part_Active FROM Part WHERE Part_id = " + partID);

    if (query.exec() == false){
        //qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Update_Part::Load_Part_Info_to_Form()");
    }else{
        while(query.next())
        {
            ui->line_Name->setText(query.value(0).toString()); //Name
            ui->txt_Part_Description->setPlainText(query.value(1).toString()); //Description
            ui->double_Spin_Cost_Price->setValue(query.value(2).toDouble()); //Cost Price
            ui->double_Spin_Sell_Price->setValue(query.value(3).toDouble());//Sell Price
            ui->spin_Quantity->setValue(query.value(4).toInt());//Quantity

            if(query.value(5).toBool()){ //is Active?
                ui->check_btn_Part_Enabled->setChecked(true);
            }else{
                ui->check_btn_Part_Enabled->setChecked(false);
            }

        }
    }
}

void Stock_Update_Part::on_buttonBox_accepted()
{
    //Get the current ui checkbox status//
    bool Part_Active;
    if(ui->check_btn_Part_Enabled->isChecked()){
        Part_Active = true;
    }else{
        Part_Active = false;
    }
    //Get the current ui checkbox status//

    QSqlQuery Update_Part;
    Update_Part.prepare("UPDATE Part SET"
                        " Part_Name = :Part_Name,"
                        " Part_Description = :Part_Description,"
                        " Part_Cost = :Part_Cost,"
                        " Part_Sell_Price = :Part_Sell_Price,"
                        " Part_Quantity = :Part_Quantity,"
                        " Part_Active = :Part_Active "
                        " WHERE Part_id = :Part_ID");

    Update_Part.bindValue(":Part_Name", ui->line_Name->text());
    Update_Part.bindValue(":Part_Description", ui->txt_Part_Description->toPlainText());
    Update_Part.bindValue(":Part_Cost", ui->double_Spin_Cost_Price->value());
    Update_Part.bindValue(":Part_Quantity", ui->spin_Quantity->value());
    Update_Part.bindValue(":Part_Sell_Price", ui->double_Spin_Sell_Price->value());
    Update_Part.bindValue(":Part_Active", Part_Active);
    Update_Part.bindValue(":Part_ID", partID);

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
