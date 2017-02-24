#include "Service_Create_Description.h"
#include "ui_Service_Create_Description.h"
#include "System_Services_and_Info.h"

#include "QMessageBox"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QSqlError"

Service_Create_Description::Service_Create_Description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Service_Create_Description)
{
    ui->setupUi(this);
    ui->line_Short_Description->setFocus();
}

Service_Create_Description::~Service_Create_Description()
{
    delete ui;
}

bool Service_Create_Description::Verify_Empty_Fields_On_Form()
{
    if (ui->txt_Full_Description->toPlainText() == "" || ui->line_Short_Description->text() == "" )
    {
        QPixmap crying(":/emoticons/face-crying.png");
        ui->lbl_Emoticon->setPixmap(crying);
        QMessageBox::warning(this, tr("Error!"), tr("All fields need to be filled!"));
        ui->line_Short_Description->setFocus();
        return false;
    }
    //Only returns true if all the fields are filled.
    return true;
}

QString Service_Create_Description::getClientid() const
{
    return clientid;
}

void Service_Create_Description::setClientid(const QString &value)
{
    clientid = value;
}

QString Service_Create_Description::getCarID() const
{
    return CarID;
}

void Service_Create_Description::setCarID(const QString &value)
{
    CarID = value;
}

QString Service_Create_Description::getServiceID() const
{
    return ServiceID;
}

void Service_Create_Description::setServiceID(const QString &value)
{
    ServiceID = value;
}

void Service_Create_Description::on_txt_Full_Description_textChanged()
{
    if (ui->txt_Full_Description->toPlainText().length() > 1000)
    {
        QString fullserviceDescription = ui->txt_Full_Description->toPlainText();
        fullserviceDescription.chop(fullserviceDescription.length() - 1000); // Cut off at 500 characters
        ui->txt_Full_Description->setPlainText(fullserviceDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_Full_Description->textCursor();
        cursor.setPosition(ui->txt_Full_Description->document()->characterCount() - 1);
        ui->txt_Full_Description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::warning(this, tr("Error!"), tr("Keep the Part description smaller then 500 chars."));
    }
}

void Service_Create_Description::on_buttonBox_accepted()
{
    if(Verify_Empty_Fields_On_Form()){

        QSqlQuery query;
        query.prepare("INSERT INTO Service (Service_Client_id, Service_Client_Carid, Service_Short_Description, Service_Description, Service_Hour_Cost, Service_Hours_Duration)"
                      "VALUES (:Service_Client_id, :Service_Client_Carid, :Service_Short_Description, :Service_Description, :Service_Hour_Cost, :Service_Hours_Duration )");

        query.bindValue(":Service_Client_id", clientid);
        query.bindValue(":Service_Client_Carid", CarID);

        System_Services_and_Info System_Services_and_Info;
        query.bindValue(":Service_Hour_Cost", System_Services_and_Info.Get_Current_Hour_Cost());

        query.bindValue(":Service_Short_Description", ui->line_Short_Description->text());
        query.bindValue(":Service_Description", ui->txt_Full_Description->toPlainText());

        if (query.exec() == false){
            QMessageBox::critical(this, tr("Error!"), query.lastError().text() + " class Service_Create_Description::on_btn_Salvar_clicked() ");
        }else{
            ui->line_Short_Description->setFocus();
            QMessageBox::information(this, tr("Success!"), tr("Service registered on this Client's Car.\n\n"
                                                              "Now we will return to the previous screen on which this new Service "
                                                              "is available for use, there you can add used Parts, update it and do"
                                                              "all changes that you need while doing the 'Hard Work' "));
            close();
        }
    }
}

void Service_Create_Description::on_buttonBox_rejected()
{
    close();
}
