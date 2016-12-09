#ifndef ADDCLIENTCAR_H
#define ADDCLIENTCAR_H

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
    void addClientInfoToForm(QString);
    //void Setclient(QString);
    void addCar(QString);
    bool verificaCamposEmBrancoNoForm();
    void checkCarDescriptionSize();

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
