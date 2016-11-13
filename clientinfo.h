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
    void loadAll();
    void loadCarsGrid();

    QString client_id;

    QString getClient_id() const;
    void setClient_id(const QString &value);

private slots:
    void on_btn_addClientCarro_clicked();
    void on_tbl_clientCars_doubleClicked(const QModelIndex &index);

    void on_tbl_ClientServices_doubleClicked(const QModelIndex &index);

    void on_btn_atualizarCliente_clicked();

private:
    Ui::clientinfo *ui;
    void loadServicesGrid();
    void loadClientInfo_to_TextBoxes();
};

#endif // CLIENTINFO_H
