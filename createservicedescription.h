#ifndef CREATESERVICEDESCRIPTION_H
#define CREATESERVICEDESCRIPTION_H

#include <QDialog>

namespace Ui {
class CreateServiceDescription;
}

class CreateServiceDescription : public QDialog
{
    Q_OBJECT

public:
    explicit CreateServiceDescription(QWidget *parent = 0);
    ~CreateServiceDescription();
    bool verificaCamposEmBrancoNoForm();

    QString clientid;
    QString CarID;
    QString ServiceID;

    QString getServiceID() const;
    void setServiceID(const QString &value);

    QString getCarID() const;
    void setCarID(const QString &value);

    QString getClientid() const;
    void setClientid(const QString &value);

private slots:
    void on_btn_Salvar_clicked();

    void on_txt_FullDescription_textChanged();

private:
    Ui::CreateServiceDescription *ui;
};

#endif // CREATESERVICEDESCRIPTION_H
