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
    void on_action_Add_Client_triggered();
    void on_action_Add_Part_triggered();
    void on_tbl_Services_History_doubleClicked(const QModelIndex &index);
    void on_action_Exit_triggered();
    void on_action_About_Oficina_triggered();
    void on_line_ID_or_CPF_or_Name_textChanged(const QString &arg1);

    void on_action_Stock_triggered();

    void on_action_Change_Hour_Cost_triggered();

    void on_action_Manpage_triggered();

    void on_buttonBox_accepted();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
