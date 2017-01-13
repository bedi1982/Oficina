#ifndef STOCK_PARTS_SELECTION_H
#define STOCK_PARTS_SELECTION_H

#include <QDialog>

namespace Ui {
class Stock_Parts_Selection;
}

class Stock_Parts_Selection : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Parts_Selection(QWidget *parent = 0);
    ~Stock_Parts_Selection();

    QString serviceID;

    void setServiceID(QString serviceid);

    QString getServiceID() const;

private slots:
    void on_line_Part_Name_textChanged(const QString &arg1);

    void on_tbl_Parts_List_doubleClicked(const QModelIndex &index);

    void on_btn_Add_Part_to_Stock_clicked();

private:
    Ui::Stock_Parts_Selection *ui;
};

#endif // PARTSSELECTIONFROMLIST_H
