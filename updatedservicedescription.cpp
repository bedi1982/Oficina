#include "updatedservicedescription.h"
#include "ui_updatedservicedescription.h"
#include "QSqlQueryModel"
#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"

Updatedservicedescription::Updatedservicedescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Updatedservicedescription)
{
    ui->setupUi(this);
}

Updatedservicedescription::~Updatedservicedescription()
{
    delete ui;
}

void Updatedservicedescription::SetDescription(){
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT Service_Description, Service_Short_Description from Service where Service_id  = " + serviceID);

    if(model->query().isSelect()){
        ui->txt_FullDescription->setText(model->data(model->index(0, 0)).toString());
        ui->line_ShortDescription ->setText(model->data(model->index(0, 1)).toString());
        }
}

void Updatedservicedescription::EnableDescriptionUpdate(){
    QSqlQuery UpdateServiceDescription;
    UpdateServiceDescription.prepare("Update Service set Service_Description = :Service_Description, Service_Short_Description = :Service_Short_Description where Service_id =" + serviceID);

    UpdateServiceDescription.bindValue(":Service_Description", ui->txt_FullDescription->toPlainText());
    UpdateServiceDescription.bindValue(":Service_Short_Description", ui->line_ShortDescription->text());

    if (!(UpdateServiceDescription.exec())){
        QMessageBox::critical(this, "Erro!", UpdateServiceDescription.lastError().text() + "class Updatedservicedescription.cpp  EnableDescriptionUpdate()");
    }else{
        QMessageBox::critical(this, "Sucesso!", "Descrição do Serviço atualizada.");
        close();
    }
}

QString Updatedservicedescription::getServiceID() const
{
    return serviceID;
}

void Updatedservicedescription::setServiceID(const QString &value)
{
    serviceID = value;
}

void Updatedservicedescription::on_btn_salvar_clicked()
{
 EnableDescriptionUpdate();
}

void Updatedservicedescription::on_txt_FullDescription_textChanged()
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
