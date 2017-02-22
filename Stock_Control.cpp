#include "QSqlTableModel"
#include "QAbstractItemModel"
#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"

#include "Stock_Control.h"
#include "ui_Stock_Control.h"
#include "Stock_Update_Part.h"


Stock_Control::Stock_Control(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock_Control)
{
    ui->setupUi(this);
    ui->line_Part_Name->setFocus();
}

Stock_Control::~Stock_Control()
{
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

void Stock_Control::on_line_Part_Name_textChanged(const QString &arg1)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(arg1.isEmpty()))
    {
        model->setTable("Part");

        if(!(arg1 == "*")){
            model->setFilter("Part_Name like '%" + arg1 + "%'");
        }

        model->select();

        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Description"));
        model->setHeaderData(3, Qt::Horizontal, tr("Cost"));
        model->setHeaderData(4, Qt::Horizontal, tr("In Stock"));
        //model->setHeaderData(4, Qt::Horizontal, tr("Used"));
        model->setHeaderData(5, Qt::Horizontal, tr("Last Updated"));
        model->setHeaderData(6, Qt::Horizontal, tr("Created At"));

        ui->tbl_Parts->setModel(model);
        ui->tbl_Parts->hideColumn(2);
        model->sort(5, Qt::DescendingOrder); //Order by last update date
        ui->tbl_Parts->resizeColumnsToContents();
    }else{
        //To clear the grid(but keep the header intact) if the user deletes a former *//
        model->clear();
        ui->tbl_Parts->setModel(model);
        ui->tbl_Parts->hideColumn(2);
    }
}

void Stock_Control::on_buttonBox_rejected()
{
    close();
}

void Stock_Control::on_tbl_Parts_doubleClicked(const QModelIndex &Selected_Part_in_The_Grid)
{
    //Get the Part ID
    const QAbstractItemModel * model = Selected_Part_in_The_Grid.model();
    QVariant part_index = model->data(model->index(Selected_Part_in_The_Grid.row(), 0, Selected_Part_in_The_Grid.parent()), Qt::DisplayRole);
    QVariant part_name = model->data(model->index(Selected_Part_in_The_Grid.row(), 1, Selected_Part_in_The_Grid.parent()), Qt::DisplayRole);
    partID = part_index.toString();
    partName = part_name.toString();

    Stock_Update_Part Stock_Update_Part;
    Stock_Update_Part.setModal(true);
    Stock_Update_Part.setPartID(partID);

    //QMessageBox::warning(this, tr("Test!"), partID + " <- Part ID clicked");
    //ui->line_Part_Name->setText("");
    Stock_Update_Part.Load_Part_Info_to_Form();
    Stock_Update_Part.exec();

    //Reset list//
    ui->line_Part_Name->setText("");
    ui->line_Part_Name->setText("*");
}

void Stock_Control::on_tbl_Parts_clicked(const QModelIndex &selectedClientinTheGrid)
{
        const QAbstractItemModel * model = selectedClientinTheGrid.model();
        QVariant part_index = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
        partID = part_index.toString();

        QVariant partdescription = model->data(model->index(selectedClientinTheGrid.row(), 2, selectedClientinTheGrid.parent()), Qt::DisplayRole);

        ui->txt_Part_Description->setText(partdescription.toString());
}
