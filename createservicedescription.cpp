#include "createservicedescription.h"
#include "ui_createservicedescription.h"
#include "QMessageBox"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QSqlError"

CreateServiceDescription::CreateServiceDescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateServiceDescription)
{
    ui->setupUi(this);
}

CreateServiceDescription::~CreateServiceDescription()
{
    delete ui;
}

bool CreateServiceDescription::verificaCamposEmBrancoNoForm()
{
    if (ui->txt_FullDescription->toPlainText() == "" || ui->line_ShortDescription->text() == "" )
    {
       // ui->lbl_Feedback->setText("Erro: Todos os campos devem estar preenchidos!");
        //QPixmap crying(":/emoticons/face-crying.png");
        //ui->lbl_Emoticon->setPixmap(crying);
        QMessageBox::critical(this, "Erro!", "Todos os campos devem estar preenchidos!");
        ui->line_ShortDescription->setFocus();    
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

QString CreateServiceDescription::getClientid() const
{
    return clientid;
}

void CreateServiceDescription::setClientid(const QString &value)
{
    clientid = value;
}

QString CreateServiceDescription::getCarID() const
{
    return CarID;
}

void CreateServiceDescription::setCarID(const QString &value)
{
    CarID = value;
}

QString CreateServiceDescription::getServiceID() const
{
    return ServiceID;
}

void CreateServiceDescription::setServiceID(const QString &value)
{
    ServiceID = value;
}


void CreateServiceDescription::on_btn_Salvar_clicked()
{
    if(verificaCamposEmBrancoNoForm()){
        //We begin This block is to save current hour cost to this service//
        QSqlQueryModel* getHourCostFromDB = new QSqlQueryModel;
        getHourCostFromDB->setQuery("select HourCost from HourCost");
        double CurrentHourCost = getHourCostFromDB->data(getHourCostFromDB->index(0,0)).toDouble();
        //END This block is to save current hour cost to service//

        QSqlQuery query;
        query.prepare("insert into Service (Service_Client_id, Service_Client_Carid, Service_Short_Description, Service_Description, Service_Hour_Cost, Service_Hours_Duration)"
                      "values (:Service_Client_id, :Service_Client_Carid, :Service_Short_Description, :Service_Description, :Service_Hour_Cost, :Service_Hours_Duration )");

        query.bindValue(":Service_Client_id", clientid);
        query.bindValue(":Service_Client_Carid", CarID);
        query.bindValue(":Service_Hour_Cost", CurrentHourCost);
        query.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());
        query.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());
        //query.bindValue(":Service_Hours_Duration", ui->Spin_HandWorkHours->text().toDouble());

        if (query.exec() == false){
            QMessageBox::critical(this, "Erro!", query.lastError().text() + " class addservice.cpp on_btn_Salvar_clicked() ");
        }else{
         //   ui->lbl_Feedback->setText("Serviço adicionado!");
         //  QPixmap cool(":/emoticons/face-cool.png");
         // ui->lbl_Emoticon->setPixmap(cool);
            ui->line_ShortDescription->setFocus();
            QMessageBox::information(this, "Sucesso!", "Serviço registrado para este carro e cliente."
                                                       "\nAgora voltaremos para a tela anterior onde e a nova ordem de serviço"
                                                       "\n estará visível. Lá você pode adicionar as peças que for usando neste"
                                                       " serviço. As peças também pode ser adicionadas depois.");
          //  ui->btn_Add_PartsUsedInTheService->setEnabled(true);
            close();
        }
    }
}

void CreateServiceDescription::on_txt_FullDescription_textChanged()
{
    if (ui->txt_FullDescription->toPlainText().length() > 1000)
    {
        QString fullserviceDescription = ui->txt_FullDescription->toPlainText();
        fullserviceDescription.chop(fullserviceDescription.length() - 1000); // Cut off at 500 characters
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
        QMessageBox::critical(this, "Erro!", "Mantenha a descrição do serviço menor do que 500 letras.");
    }
}
