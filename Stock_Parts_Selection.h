#ifndef Stock_Parts_Selection_H
#define Stock_Parts_SelectioN_H

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
    void on_line_NomeDaPeca_textChanged(const QString &arg1);

    void on_tbl_PartsList_doubleClicked(const QModelIndex &index);

private:
    Ui::Stock_Parts_Selection *ui;
};

#endif // PARTSSELECTIONFROMLIST_H
