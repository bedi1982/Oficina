#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_Window(QWidget *parent = 0);
    ~Main_Window();

private slots:
    void on_actionAddCliente_triggered();
    void on_actionAddPeca_triggered();
    void on_tbl_historicoServicos_doubleClicked(const QModelIndex &index);
    void on_actionSair_triggered();
    void on_actionSobreOficina_triggered();
    void on_line_RGouCPFouNome_textChanged(const QString &arg1);

    void on_actionEstoque_triggered();

    void on_actionAlterar_Custo_da_Hora_triggered();

    void on_actionManual_do_usu_rio_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
