#ifndef CLIENTCAR_ADD_CAR_H
#define CLIENTCAR_ADD_CAR_H

#include <QDialog>

namespace Ui {
class Client_Add_Car;
}

class Client_Add_Car : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Add_Car(QWidget *parent = 0);
    ~Client_Add_Car();
    void Add_Client_Info_To_Form(QString);
    //void Setclient(QString);
    void Add_Car(QString);
    bool Verify_Empty_Fields_On_Form();
    void Check_Car_Description_Size();

    QString client;

    QString getClient() const;
    void setClient(const QString &value);

private slots:
    void on_btn_Add_clicked();
    void on_txtPlain_Description_textChanged();

private:
    Ui::Client_Add_Car *ui;
};

#endif // ADDCLIENTCAR_H
