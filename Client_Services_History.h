#ifndef CLIENT_SERVICES_HISTORY_H
#define CLIENT_SERVICES_HISTORY_H

#include <QDialog>

namespace Ui {
class Client_Services_History;
}

class Client_Services_History : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Services_History(QWidget *parent = 0);
    ~Client_Services_History();
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
    Ui::Client_Services_History *ui;
    void loadServicesGrid();
    void loadClientInfo_to_TextBoxes();
};

#endif // CLIENTINFO_H
