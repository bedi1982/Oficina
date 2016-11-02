#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAddCliente_triggered();
    void on_actionAddPeca_triggered();
    void on_tbl_historicoServicos_doubleClicked(const QModelIndex &index);
    void on_actionSair_triggered();
    void on_actionSobreOficina_triggered();
    void on_line_RGouCPFouNome_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
