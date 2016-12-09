#ifndef ADDPART_H
#define ADDPART_H

#include <QDialog>

namespace Ui {
class Stock_Add_Part;
}

class Stock_Add_Part : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Add_Part(QWidget *parent = 0);
    ~Stock_Add_Part();

private slots:
    void on_btn_Sair_clicked();
    void on_btn_Cadastrar_clicked();
    bool verificaCamposEmBrancoNoForm();
    void on_txt_PartDescription_textChanged();
    void checkCarDescriptionSize();

private:
    Ui::Stock_Add_Part *ui;
};

#endif // ADDPART_H
