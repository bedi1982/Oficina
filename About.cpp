#include "About.h"
#include "ui_About.h"
#include "System_Services_and_Info.h"
#include "QSettings"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    LoadSettings();
    ui->textBrowser->setText(System_Services_and_Info::get_System_About() + System_Services_and_Info::get_System_Version());
    this->setWindowTitle(System_Services_and_Info::get_System_Version());
}

About::~About()
{
    SaveSettings();
    delete ui;
}

void About::on_buttonBox_rejected()
{
    close();
}

void About::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("About");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}

void About::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("About");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
