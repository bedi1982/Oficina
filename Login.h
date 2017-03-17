#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    bool Verify_Empty_Fields_on_Form();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
