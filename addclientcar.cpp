#include "addclientcar.h"
#include "ui_addclientcar.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "clientinfo.h"
#include "QMessageBox"


QString client;

addclientcar::addclientcar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addclientcar)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
    ui->lbl_Feedback->setText("Todos os campos devem estar preenchidos.");
}

addclientcar::~addclientcar()
{
    delete ui;
}

void addclientcar::Setclient(QString client_id){
    client = client_id;
}

bool addclientcar::verificaCamposEmBrancoNoForm()
{
    if (   ui->txt_Model->text() == ""
           ||ui->txt_Year->text() == ""
           ||ui->txtPlain_Description->toPlainText() == ""
           ||ui->txt_Placa->text() == ""
           ||ui->txt_Color->text()== ""
           )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->txt_Model->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addclientcar::addClientInfoToForm(QString client_id){
    QSqlQuery query;
    query.prepare("SELECT Client_Name FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, "Erro!", query.lastError().text() + ". Class: addclient.cpp56");
    }
    while(query.next())
    {
        ui->line_NomeCliente->setText(query.value(0).toString());
    }

}

void addclientcar::addCar(QString client_id){
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into ClientCar (ClientCar_Client_id, ClientCar_Model, ClientCar_Description, ClientCar_BuiltYear, ClientCar_Placa, ClientCar_Color)"
                      "values (:ClientId, :Model, :Description, :BuiltYear, :Placa, :Color)");

        query.bindValue(":ClientId", client_id);
        query.bindValue(":Model", ui->txt_Model->text());
        query.bindValue(":Description", ui->txtPlain_Description->toPlainText());
        query.bindValue(":BuiltYear", ui->txt_Year->text());
        query.bindValue(":Placa", ui->txt_Placa->text());
        query.bindValue(":Color", ui->txt_Color->text());

        if (query.exec() == false){
            qDebug() << query.lastError();
            ui->lbl_Feedback->setText("Erro Grave. Fale com o desenvolvedor.");
            QMessageBox::critical(this, "Erro!", query.lastError().text() + ". Class: addclieentcar.cpp81");
        }else{
            ui->lbl_Feedback->setText("Carro adicionado ao Cliente!");
            QPixmap cool(":/emoticons/face-cool.png");
            ui->lbl_Emoticon->setPixmap(cool);
            QMessageBox::information(this, "Sucesso!", "Carro adicionado ao registro do Cliente.");
             close();
        }
    }
    //Car added, so we close this window//
}

//Check car description size//
void addclientcar::checkCarDescriptionSize(){
    if (ui->txtPlain_Description->toPlainText().length() > 300)
    {
        QString carDescription = ui->txtPlain_Description->toPlainText();
        carDescription.chop(carDescription.length() - 300); // Cut off at 300 characters
        ui->txtPlain_Description->setPlainText(carDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txtPlain_Description->textCursor();
        cursor.setPosition(ui->txtPlain_Description->document()->characterCount() - 1);
        ui->txtPlain_Description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::critical(this,
                              "Erro!",
                              "Mantenha a descrição menor do que 300 letras.");
    }
}
//Check car description size//

void addclientcar::on_btn_Add_clicked()
{
    addCar(client);
}

void addclientcar::on_txtPlain_Description_textChanged()
{
    checkCarDescriptionSize();
}
