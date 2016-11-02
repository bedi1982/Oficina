#include "addpart.h"
#include "ui_addpart.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "QMessageBox"

addpart::addpart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addpart)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->doubleSpinCusto->setMaximum(9999);
}

addpart::~addpart()
{
    delete ui;
}

bool addpart::verificaCamposEmBrancoNoForm()
{
    if (   ui->line_Nome->text() == ""
           ||ui->txt_PartDescription->toPlainText() == ""
           ||ui->doubleSpinCusto->text() == ""
           ||ui->spin_Quantidade->text() == ""
       )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->line_Nome->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addpart::on_btn_Sair_clicked()
{
    close();
}

void addpart::on_btn_Cadastrar_clicked()
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
            QMessageBox::critical(this, "Erro!", "Esta peça não foi adicionado!!(class addpart.cpp).");
        }else{
        ui->lbl_Feedback->setText(ui->line_Nome->text() + " adicionado ao estoque!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        QMessageBox::information(this, "Sucesso!", "Carro adicionado ao registro do Cliente.");
        }
    }
}

//Check car description Filed size(This function only limits entered text to 100)//
void addpart::checkCarDescriptionSize(){
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
        QMessageBox::critical(this,
                              "Erro!",
                              "Mantenha a descrição da peça menor do que 100 letras.");
    }
}


void addpart::on_txt_PartDescription_textChanged()
{
    checkCarDescriptionSize();
}
