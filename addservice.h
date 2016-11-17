#ifndef ADDSERVICE_H
#define ADDSERVICE_H

#include <QDialog>

namespace Ui {
class addservice;
}

class addservice : public QDialog
{
    Q_OBJECT

public:
    explicit addservice(QWidget *parent = 0);
    ~addservice();

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

private:
    Ui::addservice *ui;
};

#endif // ADDSERVICE_H
