#include "QSqlTableModel"
#include "QAbstractItemModel"
#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"

#include "Stock_Control.h"
#include "ui_Stock_Control.h"
#include "Stock_Update_Part.h"
#include "Stock_Add_Part.h"
#include "QSettings"


Stock_Control::Stock_Control(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Control)
{
    ui->setupUi(this);
    LoadSettings();
    ui->line_Part_Name->setFocus();
    ui->line_Part_Name->setText("*");
    ui->spinBox_Quantity_to_Show->setEnabled(false);
}

Stock_Control::~Stock_Control()
{
    SaveSettings();
    delete ui;
}

QString Stock_Control::getPartName() const
{
    return partName;
}

void Stock_Control::setPartName(const QString &value)
{
    partName = value;
}

QString Stock_Control::getPartID() const
{
    return partID;
}

void Stock_Control::setPartID(const QString &value)
{
    partID = value;
}

void Stock_Control::on_line_Part_Name_textChanged(const QString &Search_String)
{

    QSqlTableModel* model = new QSqlTableModel;

    if(!(Search_String.isEmpty()))
    {
        model->setTable("Part");

        int Filtered_Quantity = ui->spinBox_Quantity_to_Show->value();

        //Filter for *//
        if((Search_String != "*") && (ui->checkBox_Set_Quantity->isChecked())){
            model->setFilter(QString("Part_Name like '%" + Search_String + "%' AND Part_Quantity <= %1").arg(Filtered_Quantity));
            qDebug() << "TEST: não estrela e check";
        }else{
            if((Search_String == "*") && (ui->checkBox_Set_Quantity->isChecked())){
                model->setFilter(QString("Part_Quantity <= %1").arg(Filtered_Quantity));
                //model->setFilter("Part_Quantity <= " +  Filtered_Quantity);
            qDebug() << "TEST: sim estrela e check";
            }
        }
        if((Search_String != "*") && (!ui->checkBox_Set_Quantity->isChecked())){
            model->setFilter("Part_Name like '%" + Search_String + "%' ");
            qDebug() << "TEST: nao estrela e nao check";
        }

        model->select();

        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Group"));
        model->setHeaderData(3, Qt::Horizontal, tr("Brand"));
        model->setHeaderData(4, Qt::Horizontal, tr("Description"));
        model->setHeaderData(5, Qt::Horizontal, tr("Paying"));
        model->setHeaderData(6, Qt::Horizontal, tr("Selling"));
        model->setHeaderData(7, Qt::Horizontal, tr("In Stock")); //Quantity in stock
        model->setHeaderData(8, Qt::Horizontal, tr("Interrest Rate %"));
        model->setHeaderData(9, Qt::Horizontal, tr("Updated"));
        model->setHeaderData(10, Qt::Horizontal, tr("Created"));

        ui->tbl_Parts->setModel(model);

        //ui->tbl_Parts->hideColumn(0); //sysID
        //ui->tbl_Parts->hideColumn(2); //Description - To big for a grid (it has it's own text box)

        model->sort(6, Qt::AscendingOrder); //Quantity in stock
        ui->tbl_Parts->resizeColumnsToContents();

    }else{
        //To clear the grid(but keep the header intact) if the user deletes a former *//
        model->clear();
        ui->tbl_Parts->setModel(model);
        //ui->tbl_Parts->hideColumn(2);
    }
}

void Stock_Control::on_buttonBox_rejected()
{
    close();
}

void Stock_Control::on_tbl_Parts_doubleClicked(const QModelIndex &Selected_Part)
{
    //Get the Part ID
    const QAbstractItemModel * model = Selected_Part.model();
    QVariant part_index = model->data(model->index(Selected_Part.row(), 0, Selected_Part.parent()), Qt::DisplayRole);
    QVariant part_name = model->data(model->index(Selected_Part.row(), 1, Selected_Part.parent()), Qt::DisplayRole);
    partID = part_index.toString();
    partName = part_name.toString();

    Stock_Update_Part Stock_Update_Part;
    Stock_Update_Part.setPartID(partID);
    //TODO HERE IS A BUG WHEN EDTING VIA GUI
    qDebug() << "TEST: " + partID + " <- Part ID clicked";
    //ui->line_Part_Name->setText("");
    Stock_Update_Part.Load_Part_Info_to_Form();
    Stock_Update_Part.exec();

    //Reset list//
    ui->line_Part_Name->setText("");
    ui->line_Part_Name->setText("*");
}

void Stock_Control::on_tbl_Parts_clicked(const QModelIndex &Selected_Client)
{
        const QAbstractItemModel * model = Selected_Client.model();
        QVariant part_index = model->data(model->index(Selected_Client.row(), 0, Selected_Client.parent()), Qt::DisplayRole);
        partID = part_index.toString();

        QVariant partdescription = model->data(model->index(Selected_Client.row(), 2, Selected_Client.parent()), Qt::DisplayRole);

        ui->txt_Part_Description->setText(partdescription.toString());
}

void Stock_Control::on_spinBox_Quantity_to_Show_valueChanged()
{
    //keeps the original filter
    on_line_Part_Name_textChanged(ui->line_Part_Name->text());
}

void Stock_Control::on_checkBox_Set_Quantity_toggled()
{
    if(ui->checkBox_Set_Quantity->isChecked()){
        ui->spinBox_Quantity_to_Show->setEnabled(true);
        //TODO fix bellow xnx//
        ui->spinBox_Quantity_to_Show->setValue(9);
        ui->spinBox_Quantity_to_Show->setValue(10);
    }else{
        ui->spinBox_Quantity_to_Show->setEnabled(false);
        on_line_Part_Name_textChanged(ui->line_Part_Name->text());
    }
}

void Stock_Control::on_pushButton_clicked()
{
    Stock_Add_Part Stock_Add_Part;
    Stock_Add_Part.exec();
    on_line_Part_Name_textChanged(ui->line_Part_Name->text());
}

void Stock_Control::LoadSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Control");
    QRect myrect = setting.value("position").toRect();
    setGeometry(myrect);
    setting.endGroup();
}

void Stock_Control::SaveSettings()
{
    QSettings setting("bedi1982","Oficina");
    setting.beginGroup("Stock_Control");
    setting.setValue("position",this->geometry());
    setting.endGroup();
}
