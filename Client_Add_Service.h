#ifndef CLIENT_ADD_SERVICE_H
#define CLIENT_ADD_SERVICE_H

#include <QDialog>

namespace Ui {
class Client_Add_Service;
}

class Client_Add_Service : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Add_Service(QWidget *parent = 0);
    ~Client_Add_Service();

    void LoadPartsAndServiceCostsGrid();
    void SumCosts();
    void EnableDescriptionUpdate();
    void addserviceDescriptionText();

    QString clientid;
    QString CarID;
    QString ServiceID;


    QString getClientid() const;
    void setClientid(const QString &value);

    QString getCarID() const;
    void setCarID(const QString &value);

    QString getServiceID() const;
    void setServiceID(const QString &value);

private slots:
    void on_btn_Sair_clicked();
    void on_btn_Add_PartsUsedInTheService_clicked();
    void on_btn_save_hoursWorked_clicked();

    void on_btn_atualizarDescricaoServico_clicked();

    void on_tbl_PartsUsedInService_doubleClicked(const QModelIndex &index);

    void on_check_Pago_clicked();

private:
    Ui::Client_Add_Service *ui;
};

#endif // ADDSERVICE_H
