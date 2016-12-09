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
    ui->doubleSpinCusto->setMaximum(9999);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

Stock_Add_Part::~Stock_Add_Part()
{
    delete ui;
}

bool Stock_Add_Part::verificaCamposEmBrancoNoForm()
{
    if (   ui->line_Nome->text() == ""
           ||ui->txt_PartDescription->toPlainText() == ""
           ||ui->doubleSpinCusto->text() == ""
           ||ui->spin_Quantidade->text() == ""
           )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        ui->line_Nome->setFocus();
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Stock_Add_Part::on_btn_Sair_clicked()
{
    close();
}

void Stock_Add_Part::on_btn_Cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into Part (Part_Name, Part_Description, Part_Cost, Part_Quantity)"
                      "values (:Name, :Description, :Cost, :Quantity)");

        query.bindValue(":Name", ui->line_Nome->text());
        query.bindValue(":Description", ui->txt_PartDescription->toPlainText());
        query.bindValue(":Cost", ui->doubleSpinCusto->text().toDouble());
        query.bindValue(":Quantity", ui->spin_Quantidade->text().toInt());

        if (query.exec() == false){
            qDebug() << query.lastError();
            QMessageBox::critical(this, "Erro!", "Esta peça não foi adicionado!!(addpart::on_btn_Cadastrar_clicked()");
        }else{
            ui->lbl_Feedback->setText(ui->line_Nome->text() + " adicionado ao estoque!");
            QMessageBox::information(this, "Sucesso!", "Peça adicionada no estoque.");
            close();
        }
    }
}

//Check car description Filed size(This function only limits entered text to 250)//
void Stock_Add_Part::checkCarDescriptionSize(){
    if (ui->txt_PartDescription->toPlainText().length() > 250)
    {
        QString partDescription = ui->txt_PartDescription->toPlainText();
        partDescription.chop(partDescription.length() - 250); // Cut off at 100 characters
        ui->txt_PartDescription->setPlainText(partDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_PartDescription->textCursor();
        cursor.setPosition(ui->txt_PartDescription->document()->characterCount() - 1);
        ui->txt_PartDescription->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::critical(this, "Erro!", "Mantenha a descrição da peça menor do que 250 letras.");
    }
}

void Stock_Add_Part::on_txt_PartDescription_textChanged()
{
    checkCarDescriptionSize();
}
