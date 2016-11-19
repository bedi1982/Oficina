#include "manul.h"
#include "ui_manul.h"

Manul::Manul(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manul)
{
    ui->setupUi(this);
}

Manul::~Manul()
{
    delete ui;
}
