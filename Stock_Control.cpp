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
    QPixmap cool(":/emoticons/face-cool.png");
    ui->lbl_Emoticon->setPixmap(cool);
    ui->line_NomeDaPeca->setFocus();
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

void Stock_Control::on_line_NomeDaPeca_textChanged(const QString &arg1)
{
    QSqlTableModel* model = new QSqlTableModel;

    ui->btn_save->setEnabled(true);
    ui->txt_description->setEnabled(true);

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
        model->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        model->setHeaderData(2, Qt::Horizontal, tr("Descrição"));
        model->setHeaderData(3, Qt::Horizontal, tr("Custo"));
        model->setHeaderData(4, Qt::Horizontal, tr("Em Estoque"));
        //model->setHeaderData(4, Qt::Horizontal, tr("Usada"));
        model->setHeaderData(5, Qt::Horizontal, tr("Última Atualização"));
        model->setHeaderData(6, Qt::Horizontal, tr("Adicionada em"));
        ui->tbl_parts->setModel(model);
        ui->tbl_parts->hideColumn(2);
        ui->tbl_parts->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_parts->setModel(model);
        ui->tbl_parts->hideColumn(2);
        ui->tbl_parts->resizeColumnsToContents();
    }
}

void Stock_Control::on_tbl_parts_clicked(const QModelIndex &selectedClientinTheGrid)
{
    const QAbstractItemModel * model = selectedClientinTheGrid.model();
    QVariant part_index = model->data(model->index(selectedClientinTheGrid.row(), 0, selectedClientinTheGrid.parent()), Qt::DisplayRole);
    partID = part_index.toString();

    QVariant partdescription = model->data(model->index(selectedClientinTheGrid.row(), 2, selectedClientinTheGrid.parent()), Qt::DisplayRole);

    ui->txt_description->setText(partdescription.toString());
}

void Stock_Control::on_btn_save_clicked()
{
    QSqlQuery UpdatePartDescription;
    UpdatePartDescription.prepare("Update Part set Part_Description = :Part_Description where Part_id = :partID");

    UpdatePartDescription.bindValue(":Part_Description", ui->txt_description->toPlainText());
    UpdatePartDescription.bindValue(":partID", partID);

    if (!(UpdatePartDescription.exec())){
        QMessageBox::critical(this, "Erro!", UpdatePartDescription.lastError().text() + "class Stock_Control::on_btn_save_clicked()");
    }else{
        QMessageBox::information(this, "Sucesso!", "Descrição da peça atualizada.");
        on_line_NomeDaPeca_textChanged(ui->line_NomeDaPeca->text());
    }
}

void Stock_Control::on_btn_exit_clicked()
{
    close();
}

void Stock_Control::on_txt_description_textChanged()
{
    if (ui->txt_description->toPlainText().length() > 250)
    {
        QString txt_description = ui->txt_description->toPlainText();
        txt_description.chop(txt_description.length() - 250); // Cut off at 100 characters
        ui->txt_description->setPlainText(txt_description); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_description->textCursor();
        cursor.setPosition(ui->txt_description->document()->characterCount() - 1);
        ui->txt_description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::warning(this, "Erro!", "Mantenha a descrição da peça menor do que 250 letras.");
    }
}
