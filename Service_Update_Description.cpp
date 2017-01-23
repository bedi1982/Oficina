#include "Service_Update_Description.h"
#include "ui_Service_Update_Description.h"

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
    model->setQuery("SELECT Service_Description, Service_Short_Description from Service where Service_id  = " + serviceID);

    if(model->query().isSelect()){
        ui->txt_Full_Description->setText(model->data(model->index(0, 0)).toString());
        ui->line_Short_Description ->setText(model->data(model->index(0, 1)).toString());
        }
}

void Service_Update_Description::Enable_Description_Update(){
    QSqlQuery UpdateServiceDescription;
    UpdateServiceDescription.prepare("Update Service set Service_Description = :Service_Description, Service_Short_Description = :Service_Short_Description where Service_id =" + serviceID);

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

void Service_Update_Description::on_btn_Save_clicked()
{
 Enable_Description_Update();
}

void Service_Update_Description::on_txt_Full_Description_textChanged()
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
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the Part description smaller then 250 chars."));
    }
}
