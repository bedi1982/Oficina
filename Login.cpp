#include "Login.h"
#include "ui_Login.h"

#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "System_Services_and_Info.h"
#include "QIntValidator"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->line_ID->setPlaceholderText("Only Numbers Allowed");
    ui->line_ID->setValidator(new QIntValidator);
}

Login::~Login()
{
    delete ui;
}

bool Login::Verify_Empty_Fields_on_Form()
{
    if(ui->line_ID->text() == "" || ui->line_Password->text() == ""){
        ui->label_Feedback->setText(tr("All fields need to be filled!"));
        ui->line_ID->setFocus();
        return false;
    }
    //Only returns true when all the fields are filled.
    return true;
}

void Login::on_buttonBox_accepted()
{
    hide();
}

void Login::on_buttonBox_rejected()
{
    exit(0);
}
