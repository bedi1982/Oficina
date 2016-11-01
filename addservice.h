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
    void setClientIdandName(int, QString);

private slots:
    void on_btn_Cadastrar_clicked();
    void on_btn_Sair_clicked();
    void limpaForm();
    void checkCarDescriptionSize();
    bool verificaCamposEmBrancoNoForm();

private:
    Ui::addservice *ui;
};

#endif // ADDSERVICE_H
