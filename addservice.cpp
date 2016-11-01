#include "addservice.h"
#include "ui_addservice.h"
#include "QSqlQuery"
#include "QDebug"
#include "QSqlError"
#include "mainwindow.h"
#include "QMessageBox"

int clientid;
QString clientname;

addservice::addservice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addservice)
{
    ui->setupUi(this);
    QPixmap glasses(":/emoticons/face-glasses.png");
    ui->lbl_Emoticon->setPixmap(glasses);
}

addservice::~addservice()
{
    delete ui;
}

void addservice::limpaForm()
{
    ui->line_ShortDescription->setText("");
    ui->txt_FullDescription->setText("");
}

bool addservice::verificaCamposEmBrancoNoForm()
{
    if (ui->txt_FullDescription->toPlainText() == ""
      ||ui->line_ShortDescription->text() == ""
           )
    {
        ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        limpaForm();
        ui->line_ShortDescription->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void addservice::on_btn_Cadastrar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        QSqlQuery query;
        query.prepare("insert into Service (Service_Client_id, Service_Short_Description, Service_Description, Service_Total_Cost, Service_Parts_Cost, Service_WorkCost)"
                      "values (:Service_Client_id, :Service_Short_Description, :Service_Description, :Service_Total_Cost, :Service_Parts_Cost, :Service_WorkCost )");
        clientid = 5    ;
        query.bindValue(":Service_Client_id", clientid);
        query.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());
        query.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());
        query.bindValue(":Service_Total_Cost", ui->Spin_TotalserviceCost->text().toDouble());
        query.bindValue(":Service_Parts_Cost", ui->Spin_PartsCost->text().toDouble());
        query.bindValue(":Service_WorkCost", ui->SpinHandWorkCost->text().toDouble());

        if (query.exec() == false){
            qDebug() << query.lastError();
        }
        ui->lbl_Feedback->setText("Serviço adicionado!");
        QPixmap cool(":/emoticons/face-cool.png");
        ui->lbl_Emoticon->setPixmap(cool);
        ui->line_ShortDescription->setFocus();
        limpaForm();
    }
}

void addservice::setClientIdandName(int id, QString name)
{
    clientid = id;
    clientname = name;
    QString clientId = QString::number(id);
    qDebug() << clientId;
    ui->lbl_Feedback->setText("Adicionando serviço para " + clientname + ". Cadastro N: " + clientId);
}

//Check car description Filed size(This function only limits entered text to 00)//
void addservice::checkCarDescriptionSize(){
    if (ui->txt_FullDescription->toPlainText().length() > 500)
    {
        QString fullserviceDescription = ui->txt_FullDescription->toPlainText();
        fullserviceDescription.chop(fullserviceDescription.length() - 500); // Cut off at 500 characters
        ui->txt_FullDescription->setPlainText(fullserviceDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_FullDescription->textCursor();
        cursor.setPosition(ui->txt_FullDescription->document()->characterCount() - 1);
        ui->txt_FullDescription->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::critical(this,
                              "Erro!",
                              "Mantenha a descrição do serviço menor do que 500 letras.");
    }
}

void addservice::on_btn_Sair_clicked()
{
    close();
}
