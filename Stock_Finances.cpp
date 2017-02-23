#include "Stock_Finances.h"
#include "ui_Stock_Finances.h"

Stock_Finances::Stock_Finances(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Finances)
{
    ui->setupUi(this);
}

Stock_Finances::~Stock_Finances()
{
    delete ui;
}
