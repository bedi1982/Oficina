#ifndef MAN_PAGE_H
#define MAN_PAGE_H

#include <QDialog>

namespace Ui {
class Man_Page;
}

class Man_Page : public QDialog
{
    Q_OBJECT

public:
    explicit Man_Page(QWidget *parent = 0);
    ~Man_Page();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::Man_Page *ui;
};

#endif // MANUL_H
