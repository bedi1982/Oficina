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


    QString getPartID() const;
    void setPartID(const QString &value);

private slots:
    void on_line_Part_Name_textChanged(const QString &arg1);

    void on_tbl_Parts_clicked(const QModelIndex &index);

    void on_btn_Save_Description_clicked();

    void on_btn_Exit_clicked();

    void on_txt_Part_Description_textChanged();

private:
    Ui::Stock_Control *ui;
};

#endif // STOCKCONTROL_H
