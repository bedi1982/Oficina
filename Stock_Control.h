#ifndef STOCK_CONTROL_H
#define STOCK_CONTROL_H

#include <QDialog>

namespace Ui {
class Stock_Control;
}

class Stock_Control : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Control(QWidget *parent = 0);
    ~Stock_Control();
    QString partID;
    QString partName;

    QString getPartID() const;

    void setPartID(const QString &value);

    QString getPartName() const;
    void setPartName(const QString &value);

private slots:
    void on_line_Part_Name_textChanged(const QString &arg1);

    void on_buttonBox_rejected();

    void on_tbl_Parts_doubleClicked(const QModelIndex &Selected_Part_in_The_Grid);

    void on_tbl_Parts_clicked(const QModelIndex &index);

    void on_spinBox_Quantity_to_Show_valueChanged();

    void on_checkBox_Set_Quantity_toggled();

    void on_pushButton_clicked();

private:
    Ui::Stock_Control *ui;
};

#endif // STOCKCONTROL_H
