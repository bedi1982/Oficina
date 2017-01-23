#include "Stock_Add_Part.h"
#include "ui_Stock_Add_Part.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QMessageBox"

Stock_Add_Part::Stock_Add_Part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Add_Part)
{
    ui->setupUi(this);
    ui->double_Spin_Cost->setMaximum(9999);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

Stock_Add_Part::~Stock_Add_Part()
{
    delete ui;
}

bool Stock_Add_Part::Check_Empty_Fields_On_Form()
{
    if (   ui->line_Name->text() == ""
           ||ui->txt_Part_Description->toPlainText() == ""
           ||ui->double_Spin_Cost->text() == ""
           ||ui->spin_Quantity->text() == ""
           )
    {
        ui->lbl_Feedback->setText(tr("Error: All fields need to be filled!"));
        ui->line_Name->setFocus();
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Stock_Add_Part::on_btn_Exit_clicked()
{
    close();
}

void Stock_Add_Part::on_btn_Add_clicked()
{
    if(Check_Empty_Fields_On_Form()){
        QSqlQuery query;
        query.prepare("insert into Part (Part_Name, Part_Description, Part_Cost, Part_Quantity)"
                      "values (:Name, :Description, :Cost, :Quantity)");

        query.bindValue(":Name", ui->line_Name->text());
        query.bindValue(":Description", ui->txt_Part_Description->toPlainText());
        query.bindValue(":Cost", ui->double_Spin_Cost->text().toDouble());
        query.bindValue(":Quantity", ui->spin_Quantity->text().toInt());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), tr("This Part was not added!! Classe: Stock_Add_Part::on_btn_Cadastrar_clicked()"));
        }else{
            ui->lbl_Feedback->setText(ui->line_Name->text() + tr(" added to Stock!"));
            QMessageBox::information(this, tr("Success!"), tr("Part added to Stock."));
            close();
        }
    }
}

//Check car description Filed size(This function only limits entered text to 250)//
void Stock_Add_Part::check_Car_Description_Size(){
    if (ui->txt_Part_Description->toPlainText().length() > 250)
    {
        QString partDescription = ui->txt_Part_Description->toPlainText();
        partDescription.chop(partDescription.length() - 250); // Cut off at 100 characters
        ui->txt_Part_Description->setPlainText(partDescription); // Reset text

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

void Stock_Add_Part::on_txt_Part_Description_textChanged()
{
    check_Car_Description_Size();
}
