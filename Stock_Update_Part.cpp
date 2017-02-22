#include "Stock_Update_Part.h"
#include "ui_Stock_Update_Part.h"

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
    query.prepare("SELECT Part_Name, Part_Description, Part_Cost, Part_Quantity FROM Part WHERE Part_id = " + partID);

    if (query.exec() == false){
        //qDebug() << query.lastError();
        //QMessageBox::critical(this, tr("Error!"), query.lastError().text() + ". void Stock_Update_Part::Load_Part_Info_to_Form()");
    }else{
        while(query.next())
        {
            ui->line_Name->setText(query.value(0).toString()); //Name
            ui->txt_Part_Description->setPlainText(query.value(1).toString()); //Description
            ui->double_Spin_Cost->setValue(query.value(2).toDouble());
            ui->spin_Quantity->setValue(query.value(3).toInt());
        }
    }
}

void Stock_Update_Part::on_buttonBox_accepted()
{
    QSqlQuery Update_Part;
    Update_Part.prepare("UPDATE Part SET"
                        " Part_Name = :Part_Name,"
                        " Part_Description = :Part_Description,"
                        " Part_Cost = :Part_Cost,"
                        " Part_Quantity = :Part_Quantity"
                        " WHERE Part_id = :Part_ID");

    Update_Part.bindValue(":Part_Name", ui->line_Name->text());
    Update_Part.bindValue(":Part_Description", ui->txt_Part_Description->toPlainText());
    Update_Part.bindValue(":Part_Cost", ui->double_Spin_Cost->value());
    Update_Part.bindValue(":Part_Quantity", ui->spin_Quantity->value());
    Update_Part.bindValue(":Part_ID", partID);

    if (!(Update_Part.exec())){
        QMessageBox::critical(this, tr("Error!"), Update_Part.lastError().text() + "class Stock_Control::on_btn_save_clicked()");
    }else{
        QMessageBox::information(this, tr("Success!"), tr("Part Updated."));
    }
}

void Stock_Update_Part::on_txt_Part_Description_textChanged()
{
    if (ui->txt_Part_Description->toPlainText().length() > 250)
    {
        QString txt_description = ui->txt_Part_Description->toPlainText();
        txt_description.chop(txt_description.length() - 250); // Cut off at 100 characters
        ui->txt_Part_Description->setPlainText(txt_description); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_Part_Description->textCursor();
        cursor.setPosition(ui->txt_Part_Description->document()->characterCount() - 1);
        ui->txt_Part_Description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the Part description smaller then 250 chars."));
    }
}

void Stock_Update_Part::on_buttonBox_rejected()
{
    close();
}
