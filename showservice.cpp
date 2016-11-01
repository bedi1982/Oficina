#include "showservice.h"
#include "ui_showservice.h"

showService::showService(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showService)
{
    ui->setupUi(this);
}

showService::~showService()
{
    delete ui;
}
