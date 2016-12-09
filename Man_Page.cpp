#include "Man_Page.h"
#include "ui_Man_Page.h"

Man_Page::Man_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Man_Page)
{
    ui->setupUi(this);
}

Man_Page::~Man_Page()
{
    delete ui;
}
