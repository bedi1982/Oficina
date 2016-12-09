#ifndef CLIENT_EDIT_H
#define CLIENT_EDIT_H

#include <QDialog>

namespace Ui {
class Client_Edit;
}

class Client_Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Edit(QWidget *parent = 0);
    ~Client_Edit();

    QString client_id;
    void loadClientInfo_to_TextBoxes();

    QString getClient_id() const;
    void setClient_id(const QString &value);

private slots:

    void on_btn_update_clicked();

private:
    Ui::Client_Edit *ui;
};

#endif // EDITCLIENT_H
