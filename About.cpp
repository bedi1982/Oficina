#include "About.h"
#include "ui_About.h"
#include "System_Services_and_Info.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->textBrowser->setText(System_Services_and_Info::get_System_About() + System_Services_and_Info::get_System_Version());
    this->setWindowTitle(System_Services_and_Info::get_System_Version());
}

About::~About()
{
    delete ui;
}

void About::on_buttonBox_rejected()
{
    close();
}
