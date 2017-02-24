#include "About.h"
#include "ui_About.h"
#include "System_Services_and_Info.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    System_Services_and_Info System_Services_and_Info;
    ui->textBrowser->setText("Software to manage mechanical workshop services.\n"
                             "\n"
                             "Author: Sergio Rafael Lemke <bedi.com@gmail.com>\n"
                             + System_Services_and_Info.getSystem_Version());
    this->setWindowTitle(System_Services_and_Info.getSystem_Version());
}

About::~About()
{
    delete ui;
}

void About::on_buttonBox_rejected()
{
    close();
}
