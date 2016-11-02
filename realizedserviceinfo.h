#ifndef REALIZEDSERVICEINFO_H
#define REALIZEDSERVICEINFO_H

#include <QDialog>

namespace Ui {
class realizedServiceInfo;
}

class realizedServiceInfo : public QDialog
{
    Q_OBJECT

public:
    explicit realizedServiceInfo(QWidget *parent = 0);
    ~realizedServiceInfo();
    void setServiceID(QString);
    void loadAll();

private slots:
    void on_btn_Add_PartsUsedInTheService_clicked();

private:
    Ui::realizedServiceInfo *ui;
};

#endif // REALIZEDSERVICEINFO_H
