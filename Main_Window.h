#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qsortfilterproxymodel.h"
#include "QSqlTableModel"

namespace Ui {
class MainWindow;
}

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_Window(QWidget *parent = 0);

    QSqlTableModel * model;

    QSortFilterProxyModel * proxy;

    ~Main_Window();

    void Create_Client_Model_and_proxy();

    void Set_Last_Client_in_the_Grid();

private slots:

    void on_line_ID_or_CPG_or_Name_textChanged(const QString &arg1);

    void on_action_Add_Client_triggered();

    void on_action_Add_Part_triggered();

    void on_tbl_Client_List_doubleClicked(const QModelIndex &index);

    void on_action_Exit_triggered();

    void on_action_About_Oficina_triggered();

    void on_action_Stock_triggered();

    void on_action_Change_Hour_Cost_triggered();

    void on_action_Manpage_triggered();

    void on_Clear_Button_clicked();

    void on_actionStock_Finances_triggered();

    void on_action_Employees_triggered();

    void Client_Services_Open(QString clientID);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
