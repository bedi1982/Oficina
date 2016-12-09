#ifndef SERVICE_CREATE_DESCRIPTION_H
#define SERVICE_CREATE_DESCRIPTION_H

#include <QDialog>

namespace Ui {
class Service_Create_Description;
}

class Service_Create_Description : public QDialog
{
    Q_OBJECT

public:
    explicit Service_Create_Description(QWidget *parent = 0);
    ~Service_Create_Description();
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
    Ui::Service_Create_Description *ui;
};

#endif // CREATESERVICEDESCRIPTION_H
