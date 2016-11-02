#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>

namespace Ui {
class addclient;
}

class addclient : public QDialog
{
    Q_OBJECT

public:
    explicit addclient(QWidget *parent = 0);
    ~addclient();

private slots:
    bool verificaCamposEmBrancoNoForm();
    void on_btn_Sair_clicked();
    void on_btn_cadastrar_clicked();

private:
    Ui::addclient *ui;
};

#endif // ADDCLIENT_H
