#include "addcartoclient.h"
#include "ui_addcartoclient.h"

addcarToclient::addcarToclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcarToclient)
{
    ui->setupUi(this);
}

addcarToclient::~addcarToclient()
{
    delete ui;
}
