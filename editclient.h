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
    void LoadEditableGrid(QString ClientID);

private slots:
    void on_btn_sair_clicked();

private:
    Ui::EditClient *ui;
};

#endif // EDITCLIENT_H
