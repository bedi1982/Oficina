#ifndef CLIENT_UPDATE_H
#define CLIENT_UPDATE_H

#include <QDialog>

namespace Ui {
class Client_Update;
}

class Client_Update : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Update(QWidget *parent = 0);
    ~Client_Update();

    QString client_id;
    void load_Client_Info_To_TextBoxes();

    QString getClient_id() const;
    void setClient_id(const QString &value);

private slots:

    void on_btn_Client_Update_accepted();

    void on_btn_Client_Update_rejected();

private:
    Ui::Client_Update *ui;
};

#endif // EDITCLIENT_H
