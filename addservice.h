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
    void setClientIdandCar(QString client, QString car);
    void setServiceID(QString serviceid);
    void toggleFieldsToUpdateMode();
    void LoadPartsAndServiceCostsGrid();
    void SumCosts();
    void LoadServiceTitleandDetails();
    void EnableDescriptionUpdate();

private slots:
    //void on_btn_Cadastrar_clicked();
    void on_btn_Sair_clicked();
    bool verificaCamposEmBrancoNoForm();
    void on_txt_FullDescription_textChanged();

    void on_btn_Salvar_clicked();

    void on_btn_Add_PartsUsedInTheService_clicked();

    void on_btn_save_hoursWorked_clicked();

    void on_btn_atualizarDescricaoServico_clicked();

private:
    Ui::addservice *ui;
};

#endif // ADDSERVICE_H
