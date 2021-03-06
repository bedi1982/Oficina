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
    explicit Client_Add_Service(QWidget *parent = nullptr);
    ~Client_Add_Service();

    void Load_Parts_And_Service_Costs_Grid();

    void Sum_Costs();

    void Enable_Description_Update();

    void Add_Service_Description_Text();

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

    void on_check_Paid_clicked();

    void on_check_Finished_clicked();

    void on_tbl_Parts_Used_In_Service_doubleClicked(const QModelIndex &index);

    void on_btnBox_Close_rejected();

    void on_btn_Add_Parts_Used_In_The_Service_clicked();

    void on_btn_Update_Service_description_clicked();

    void on_dateTimeEdit_dateTimeChanged();

    void on_buttonBox_Close_rejected();

    void on_Button_Apply_new_Hour_Cost_clicked();

    void on_Button_Set_Worked_hours_clicked();

private:
    Ui::Client_Add_Service *ui;
    void LoadSettings();
    void SaveSettings();
};

#endif // ADDSERVICE_H
