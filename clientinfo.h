#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QDialog>

namespace Ui {
class clientinfo;
}

class clientinfo : public QDialog
{
    Q_OBJECT

public:
    explicit clientinfo(QWidget *parent = 0);
    ~clientinfo();
    void setClient_Id(QString);
    void loadAll();
    void loadCarsGrid();

private slots:

    void on_btn_addClientCarro_clicked();

    void on_btn_addService_clicked();

    void on_btn_Atualizar_clicked();

private:
    Ui::clientinfo *ui;
    void loadServicesGrid();
    void loadClientInfo_to_TextBoxes();
};

#endif // CLIENTINFO_H
