#ifndef CLIENT_SERVICES_HISTORY_H
#define CLIENT_SERVICES_HISTORY_H

#include <QDialog>

namespace Ui {
class Client_Services_History;
}

class Client_Services_History : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Services_History(QWidget *parent = 0);
    ~Client_Services_History();
    void loadAll();
    void load_Cars_Grid();

    QString client_id;

    QString getClient_id() const;
    void setClient_id(const QString &value);

private slots:
    void on_tbl_Client_Cars_doubleClicked(const QModelIndex &index);

    void on_tbl_Client_Services_doubleClicked(const QModelIndex &index);

    void on_btn_Update_Client_clicked();

    void on_btn_Add_Car_To_Client_clicked();

    void on_btn_CLose_clicked();

private:
    Ui::Client_Services_History *ui;

    void Load_Services_Grid();

    void Load_Client_Name_To_Window_Title();

    void load_Client_Info_Tab();

    void LoadSettings();

    void SaveSettings();
};

#endif // CLIENTINFO_H
