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

signals:
    void clicked();

private slots:
    void Clear_Form();

    void Set_Emoticon();

    bool Verify_Empty_Fields_on_Form();

    void on_btn_Add_Client_accepted();

    void on_btn_Add_Client_rejected();

    //Window Level//
    void on_Client_Add_finished(int result);

private:
    Ui::Client_Add *ui;

    void LoadSettings();
    void SaveSettings();

};

#endif // ADDCLIENT_H
