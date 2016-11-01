#ifndef ADDCLIENTCAR_H
#define ADDCLIENTCAR_H

#include <QDialog>

namespace Ui {
class addclientcar;
}

class addclientcar : public QDialog
{
    Q_OBJECT

public:
    explicit addclientcar(QWidget *parent = 0);
    ~addclientcar();

    void addClientInfoToForm(QString);
    void Setclient(QString);
    void addCar(QString);
    bool verificaCamposEmBrancoNoForm();
    void limpaForm();

private slots:
    void on_btn_Adcionar_clicked();

private:
    Ui::addclientcar *ui;
};

#endif // ADDCLIENTCAR_H
