#ifndef CLIENT_ADD_H
#define CLIENT_ADD_H

#include <QDialog>

namespace Ui {
class Client_Add;
}

class Client_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Add(QWidget *parent = 0);
    ~Client_Add();

private slots:
    bool verificaCamposEmBrancoNoForm();
    void on_btn_Sair_clicked();
    void on_btn_cadastrar_clicked();

private:
    Ui::Client_Add *ui;
};

#endif // ADDCLIENT_H
