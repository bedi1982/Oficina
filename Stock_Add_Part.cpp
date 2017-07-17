#include "Stock_Add_Part.h"
#include "ui_Stock_Add_Part.h"
#include "System_Services_and_Info.h"

#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QMessageBox"
#include "QSettings"

Stock_Add_Part::Stock_Add_Part(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Add_Part)
{
    ui->setupUi(this);
    LoadSettings();
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->line_Name->setFocus();
}

Stock_Add_Part::~Stock_Add_Part()
{
    SaveSettings();
    delete ui;
}

void Stock_Add_Part::Clear_Form()
{
        ui->line_Name->setText("");
        ui->txt_Part_Description->setPlainText("");
        ui->line_Brand->setText("");
        ui->double_Spin_Cost->setValue(0);
        ui->spin_Quantity->setValue(0);
        ui->double_Spin_Interest_Rate->setValue(0);
}

bool Stock_Add_Part::Check_Empty_Fields_On_Form()
{
    if (   ui->line_Name->text() == ""
           ||ui->txt_Part_Description->toPlainText() == ""
           ||ui->double_Spin_Cost->text() == ""
           ||ui->spin_Quantity->text() == ""
           ||ui->double_Spin_Interest_Rate->text() == ""
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

//Check car description Filed size(This function only limits entered text to 250)//
void Stock_Add_Part::check_Car_Description_Size(){

    const int max_size = 250;

    if(ui->txt_Part_Description->toPlainText().length() > max_size){
        ui->txt_Part_Description->setPlainText(System_Services_and_Info::Check_Text_Size(max_size, ui->txt_Part_Description->toPlainText()));

        //Warn the user:
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the text shorter then %1 chars.").arg(max_size));

        //Put cursor back to the end of the text//
        QTextCursor cursor = ui->txt_Part_Description->textCursor();
        cursor.setPosition(ui->txt_Part_Description->document()->characterCount() - 1);
        ui->txt_Part_Description->setTextCursor(cursor);
    }
}

void Stock_Add_Part::on_txt_Part_Description_textChanged()
{
    check_Car_Description_Size();
}

void Stock_Add_Part::on_buttonBox_accepted()
{
    if(Check_Empty_Fields_On_Form()){
        QSqlQuery query;
        query.prepare("INSERT INTO Part (Part_Name, Part_Brand, Part_Description, Part_Cost, Part_Sell_Value_With_Interest_Rate, Part_Quantity, Part_Interrest_Rate)"
                      " VALUES (:Name, :Brand, :Description, :Cost, :Part_Sell_Value_With_Interest_Rate, :Quantity, :Interrest_Rate)");

        query.bindValue(":Name", ui->line_Name->text());
        query.bindValue(":Brand", ui->line_Brand->text());
        query.bindValue(":Description", ui->txt_Part_Description->toPlainText());
        query.bindValue(":Cost", ui->double_Spin_Cost->value());
        query.bindValue(":Interrest_Rate", ui->double_Spin_Interest_Rate->value());

        //double_Spin_Sell_Price is percentage
        double Price_With_Interrest = ui->double_Spin_Cost->value() * ui->double_Spin_Interest_Rate->value() / 100 + ui->double_Spin_Cost->value();

        //TEST//
        qDebug() << "Cost Price: " << ui->double_Spin_Cost->value();
        qDebug() << "Inputed Interest: " << ui->double_Spin_Interest_Rate->value();
        qDebug() << "Cost Price with Interest: " << Price_With_Interrest;

        query.bindValue(":Part_Sell_Value_With_Interest_Rate", Price_With_Interrest);
        query.bindValue(":Quantity", ui->spin_Quantity->text().toInt());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Error!"), tr("This Part was not added!! Classe: Stock_Add_Part::on_btn_Cadastrar_clicked()"));
        }else{
            ui->lbl_Feedback->setText(ui->line_Name->text() + tr(" added to Stock!"));
            QMessageBox::information(this, tr("Success!"), tr("Part added to Stock."));
            Clear_Form();
            ui->line_Name->setFocus();
        }
    }
}

void Stock_Add_Part::on_buttonBox_rejected()
{
    close();
}

void Stock_Add_Part::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Add_Part");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Stock_Add_Part::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Add_Part");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
