#ifndef SERVICE_UPDATE_DESCRIPTION_H
#define SERVICE_UPDATE_DESCRIPTION_H

#include <QDialog>

namespace Ui {
class Service_Update_Description;
}

class Service_Update_Description : public QDialog
{
    Q_OBJECT

public:
    explicit Service_Update_Description(QWidget *parent = 0);
    ~Service_Update_Description();
    void Set_Description();
    void Enable_Description_Update();
    QString serviceID;

    QString getServiceID() const;
    void setServiceID(const QString &value);

private slots:

    void on_txt_Full_Description_textChanged();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Service_Update_Description *ui;
};

#endif // UPDATEDSERVICEDESCRIPTION_H
