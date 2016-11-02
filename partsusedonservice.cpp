#include "partsusedonservice.h"
#include "ui_partsusedonservice.h"

partsUsedOnService::partsUsedOnService(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::partsUsedOnService)
{
    ui->setupUi(this);
}

partsUsedOnService::~partsUsedOnService()
{
    delete ui;
}
