#ifndef ADDPART_H
#define ADDPART_H

#include <QDialog>

namespace Ui {
class addpart;
}

class addpart : public QDialog
{
    Q_OBJECT

public:
    explicit addpart(QWidget *parent = 0);
    ~addpart();

private slots:
    void on_btn_Sair_clicked();

    void on_btn_Cadastrar_clicked();

    bool verificaCamposEmBrancoNoForm();

    void limpaForm();

private:
    Ui::addpart *ui;
};

#endif // ADDPART_H
