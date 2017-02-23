#ifndef STOCK_UPDATE_PART_H
#define STOCK_UPDATE_PART_H

#include <QDialog>

namespace Ui {
class Stock_Update_Part;
}

class Stock_Update_Part : public QDialog
{
    Q_OBJECT

public:
    explicit Stock_Update_Part(QWidget *parent = 0);
    QString partID;
    ~Stock_Update_Part();

    QString getPartID() const;
    void setPartID(const QString &value);

    void Load_Part_Info_to_Form();

private slots:
    void on_buttonBox_accepted();

    void on_txt_Part_Description_textChanged();

    void on_buttonBox_rejected();

    void on_check_btn_Part_Enabled_clicked();

private:
    Ui::Stock_Update_Part *ui;

};

#endif // STOCK_UPDATE_PART_H
