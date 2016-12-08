#ifndef EDITCLIENT_H
#define EDITCLIENT_H

#include <QDialog>

namespace Ui {
class EditClient;
}

class EditClient : public QDialog
{
    Q_OBJECT

public:
    explicit EditClient(QWidget *parent = 0);
    ~EditClient();

    QString client_id;
    void loadClientInfo_to_TextBoxes();

    QString getClient_id() const;
    void setClient_id(const QString &value);

private slots:

    void on_btn_update_clicked();

private:
    Ui::EditClient *ui;
};

#endif // EDITCLIENT_H
