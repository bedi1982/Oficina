#ifndef STOCKCONTROL_H
#define STOCKCONTROL_H

#include <QDialog>

namespace Ui {
class StockControl;
}

class StockControl : public QDialog
{
    Q_OBJECT

public:
    explicit StockControl(QWidget *parent = 0);
    ~StockControl();
    QString partID;


    QString getPartID() const;
    void setPartID(const QString &value);

private slots:
    void on_line_NomeDaPeca_textChanged(const QString &arg1);

    void on_tbl_parts_clicked(const QModelIndex &index);

    void on_btn_save_clicked();

    void on_btn_exit_clicked();

    void on_txt_description_textChanged();

private:
    Ui::StockControl *ui;
};

#endif // STOCKCONTROL_H
