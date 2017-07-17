#include "Man_Page.h"
#include "ui_Man_Page.h"
#include "QSettings"


Man_Page::Man_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Man_Page)
{
    ui->setupUi(this);
    LoadSettings();
}

Man_Page::~Man_Page()
{
    SaveSettings();
    delete ui;
}

void Man_Page::on_buttonBox_rejected()
{
    close();
}

void Man_Page::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Man_Page");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Man_Page::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Man_Page");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
