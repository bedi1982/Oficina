#include "Client_Add_Car.h"
#include "ui_Client_Add_Car.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "Client_Services_History.h"
#include "QMessageBox"

Client_Add_Car::Client_Add_Car(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Add_Car)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

Client_Add_Car::~Client_Add_Car()
{
    delete ui;
}

bool Client_Add_Car::Verify_Empty_Fields_On_Form()
{
    if (   ui->txt_Model->text() == ""
           ||ui->txt_Year->text() == ""
           ||ui->txtPlain_Description->toPlainText() == ""
           ||ui->txt_Placa->text() == ""
           ||ui->txt_Color->text()== ""
           )
    {
        ui->lbl_Feedback->setText(tr("All fields need to be filled!"));
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        ui->txt_Model->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Client_Add_Car::Add_Client_Info_To_Form(QString client_id){
    QSqlQuery query;
    query.prepare("SELECT Client_Name FROM Client WHERE Client_id = " + client_id);

    if (query.exec() == false){
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + ". Class: Class: Client_Add_Car.addClientInfoToForm(QString client_id)");
    }

    while(query.next()){
        ui->line_NomeCliente->setText(query.value(0).toString());
    }
}

void Client_Add_Car::Add_Car(QString client_id){
    if(Verify_Empty_Fields_On_Form()){
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
            ui->lbl_Feedback->setText(tr("Error. Client's Car added!"));
            QMessageBox::critical(this, tr("Erro!"), query.lastError().text() + ". Class: Client_Add_Car.addCar(QString client_id)");
        }else{
            ui->lbl_Feedback->setText(tr("Car added to the Client"));
            QPixmap cool(":/emoticons/face-cool.png");
            ui->lbl_Emoticon->setPixmap(cool);
            QMessageBox::information(this, tr("Success!"), tr("Client's Car added."));
            close();
        }
    }
    //Car added, so we close this window//
}

//Check car description size//
void Client_Add_Car::Check_Car_Description_Size(){
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
        QMessageBox::warning(this,
                              tr("Error!"),
                              tr("Keep the text shortet then 300 chars."));
    }
}

QString Client_Add_Car::getClient() const
{
    return client;
}

void Client_Add_Car::setClient(const QString &value)
{
    client = value;
}
//Check car description size//

void Client_Add_Car::on_btn_Add_clicked()
{
    Add_Car(client);
}

void Client_Add_Car::on_txtPlain_Description_textChanged()
{
    Check_Car_Description_Size();
}
