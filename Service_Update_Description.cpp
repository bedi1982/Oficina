#include "Service_Update_Description.h"
#include "ui_Service_Update_Description.h"
#include "System_Services_and_Info.h"

#include "QSqlQueryModel"
#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"

Service_Update_Description::Service_Update_Description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Service_Update_Description)
{
    ui->setupUi(this);
}

Service_Update_Description::~Service_Update_Description()
{
    delete ui;
}

void Service_Update_Description::Set_Description(){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT Service_Description, Service_Short_Description FROM Service WHERE Service_id  = " + serviceID);

    if(model->query().isSelect()){
        ui->txt_Full_Description->setText(model->data(model->index(0, 0)).toString());
        ui->line_Short_Description ->setText(model->data(model->index(0, 1)).toString());
    }
}

void Service_Update_Description::Enable_Description_Update(){
    QSqlQuery UpdateServiceDescription;
    UpdateServiceDescription.prepare("Update Service SET Service_Description = :Service_Description, Service_Short_Description = :Service_Short_Description WHERE Service_id =" + serviceID);

    UpdateServiceDescription.bindValue(":Service_Description", ui->txt_Full_Description->toPlainText());
    UpdateServiceDescription.bindValue(":Service_Short_Description", ui->line_Short_Description->text());

    if (!(UpdateServiceDescription.exec())){
        QMessageBox::critical(this, tr("Error!"), UpdateServiceDescription.lastError().text() + "class Service_Update_Description::EnableDescriptionUpdate()");
    }else{
        QMessageBox::information(this, tr("Success!"), tr("Service Description Updated."));
        close();
    }
}

QString Service_Update_Description::getServiceID() const
{
    return serviceID;
}

void Service_Update_Description::setServiceID(const QString &value)
{
    serviceID = value;
}

void Service_Update_Description::on_txt_Full_Description_textChanged()
{
    const int max_size = 1000;

    if(ui->txt_Full_Description->toPlainText().length() > max_size){
        ui->txt_Full_Description->setPlainText(System_Services_and_Info::Check_Text_Size(max_size, ui->txt_Full_Description->toPlainText()));

        //Warn the user:
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the text shorter then %1 chars.").arg(max_size));

        //Put cursor back to the end of the text//
        QTextCursor cursor = ui->txt_Full_Description->textCursor();
        cursor.setPosition(ui->txt_Full_Description->document()->characterCount() - 1);
        ui->txt_Full_Description->setTextCursor(cursor);
    }
}

void Service_Update_Description::on_buttonBox_accepted()
{
    Enable_Description_Update();
}

void Service_Update_Description::on_buttonBox_rejected()
{
    close();
}
