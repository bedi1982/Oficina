#ifndef ADDCARTOCLIENT_H
#define ADDCARTOCLIENT_H

#include <QDialog>

namespace Ui {
class addcarToclient;
}

class addcarToclient : public QDialog
{
    Q_OBJECT

public:
    explicit addcarToclient(QWidget *parent = 0);
    ~addcarToclient();

private:
    Ui::addcarToclient *ui;
};

#endif // ADDCARTOCLIENT_H
