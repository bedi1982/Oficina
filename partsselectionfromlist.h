#ifndef PARTSSELECTIONFROMLIST_H
#define PARTSSELECTIONFROMLIST_H

#include <QDialog>

namespace Ui {
class partsSelectionFromList;
}

class partsSelectionFromList : public QDialog
{
    Q_OBJECT

public:
    explicit partsSelectionFromList(QWidget *parent = 0);
    ~partsSelectionFromList();

    void setServiceID(QString serviceid);

private slots:
    void on_line_NomeDaPeca_textChanged(const QString &arg1);

    void on_tbl_PartsList_doubleClicked(const QModelIndex &index);

private:
    Ui::partsSelectionFromList *ui;
};

#endif // PARTSSELECTIONFROMLIST_H
