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
    bool Verify_Empty_Fields_On_Form();

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

    void on_txt_Full_Description_textChanged();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Service_Create_Description *ui;
    void LoadSettings();
    void SaveSettings();
};

#endif // CREATESERVICEDESCRIPTION_H
