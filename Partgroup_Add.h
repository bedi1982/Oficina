#ifndef PARTGROUP_ADD_H
#define PARTGROUP_ADD_H

#include <QDialog>

namespace Ui {
class PartGroup_Add;
}

class PartGroup_Add : public QDialog
{
    Q_OBJECT

public:
    explicit PartGroup_Add(QWidget *parent = 0);
    ~PartGroup_Add();

private slots:

    void on_btn_Save_clicked();

private:
    Ui::PartGroup_Add *ui;
};

#endif // PARTGROUP_ADD_H
