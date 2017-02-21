#include "Stock_Control.h"
#include "ui_Stock_Control.h"
#include "QSqlTableModel"
#include "QAbstractItemModel"
#include "QMessageBox"
#include "QSqlQuery"
#include "QSqlError"
#include "QDebug"

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

    ui->btn_Save_Description->setEnabled(true);
    ui->txt_Part_Description->setEnabled(true);

    if(!(arg1.isEmpty()))
    {
        model->setTable("Part");

        if(!(arg1 == "*")){
            model->setFilter("Part_Name like '%" + arg1 + "%'");
        }

        model->select();
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        //ui->tbl_parts->hideColumn(0);
        //ui->tbl_parts->hideColumn(2);
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Description"));
        model->setHeaderData(3, Qt::Horizontal, tr("Cost"));
        model->setHeaderData(4, Qt::Horizontal, tr("In Stock"));
        //model->setHeaderData(4, Qt::Horizontal, tr("Used"));
        model->setHeaderData(5, Qt::Horizontal, tr("Last Updated"));
        model->setHeaderData(6, Qt::Horizontal, tr("Added At"));
        ui->tbl_Parts->setModel(model);
        ui->tbl_Parts->hideColumn(2);
        ui->tbl_Parts->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_Parts->setModel(model);
        ui->tbl_Parts->hideColumn(2);
        ui->tbl_Parts->resizeColumnsToContents();
    }
}

void Stock_Control::on_tbl_Parts_clicked(const QModelIndex &selectedClientinTheGrid)
{
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant part_index = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
    partID = part_index.toString();

    QVariant partdescription = model->data(model->index(selectedClientinTheGrid.row(), 2, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    ui->txt_Part_Description->setText(partdescription.toString());
}

void Stock_Control::on_btn_Save_Description_clicked()
{
    QSqlQuery UpdatePartDescription;
    UpdatePartDescription.prepare("Update Part set Part_Description = :Part_Description where Part_id = :partID");

    UpdatePartDescription.bindValue(":Part_Description", ui->txt_Part_Description->toPlainText());
    UpdatePartDescription.bindValue(":partID", partID);

    if (!(UpdatePartDescription.exec())){
        QMessageBox::critical(this, tr("Error!"), UpdatePartDescription.lastError().text() + "class Stock_Control::on_btn_save_clicked()");
    }else{
        QMessageBox::information(this, tr("Success!"), tr("Part Description Updated."));
        on_line_Part_Name_textChanged(ui->line_Part_Name->text());
    }
}

void Stock_Control::on_txt_Part_Description_textChanged()
{
    if (ui->txt_Part_Description->toPlainText().length() > 250)
    {
        QString txt_description = ui->txt_Part_Description->toPlainText();
        txt_description.chop(txt_description.length() - 250); // Cut off at 100 characters
        ui->txt_Part_Description->setPlainText(txt_description); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_Part_Description->textCursor();
        cursor.setPosition(ui->txt_Part_Description->document()->characterCount() - 1);
        ui->txt_Part_Description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::warning(this, tr("Warning!"), tr("Keep the Part description smaller then 250 chars."));
    }
}

void Stock_Control::on_buttonBox_rejected()
{
    close();
}
