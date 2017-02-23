#include "Employee_List.h"
#include "ui_Employee_List.h"
#include "Employee_Add.h"

#include "QSqlRelationalTableModel"
#include "QSqlQuery"
#include "QDebug"

Employee_List::Employee_List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee_List)
{
    ui->setupUi(this);
    ui->line_ID_or_CPG_or_Name->setFocus();
    ui->line_ID_or_CPG_or_Name->setText("*");
}

Employee_List::~Employee_List()
{
    delete ui;
}

void Employee_List::on_line_ID_or_CPG_or_Name_textChanged(const QString &Used_Search_Filter)
{
    QSqlTableModel* model = new QSqlTableModel;

    if(!(Used_Search_Filter.isEmpty()))
    {
        model->setTable("Employee");
        if(!(Used_Search_Filter == "*")){
            model->setFilter("Client_ID like '%" + Used_Search_Filter + "%'"
                            " OR Client_Name like '%" + Used_Search_Filter + "%'"
                            " OR Client_CPG like '%"  + Used_Search_Filter + "%'"
                            " OR Client_id like '%"   + Used_Search_Filter + "%'");
        }
        model->select();
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);

        model->setHeaderData(0, Qt::Horizontal, tr("System ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Adress"));
        model->setHeaderData(3, Qt::Horizontal, tr("City"));
        model->setHeaderData(4, Qt::Horizontal, tr("CPG"));
        model->setHeaderData(5, Qt::Horizontal, tr("ID"));
        model->setHeaderData(6, Qt::Horizontal, tr("Phone"));
        model->setHeaderData(7, Qt::Horizontal, tr("Updated at"));
        model->setHeaderData(8, Qt::Horizontal, tr("Created at"));

        ui->tbl_Services_History->setModel(model);
        ui->tbl_Services_History->hideColumn(2); //Adrees is usually to big for a grid
        ui->tbl_Services_History->resizeColumnsToContents();
    }else{
        model->clear();
        ui->tbl_Services_History->setModel(model);
        ui->tbl_Services_History->resizeColumnsToContents();
    }
}

void Employee_List::on_btn_Add_clicked()
{
    Employee_Add Employee_Add;
    Employee_Add.setModal(true);
    Employee_Add.exec();
    on_Clear_Button_clicked();
    ui->line_ID_or_CPG_or_Name->setText("*");
    close();
}

void Employee_List::on_Clear_Button_clicked()
{
    ui->line_ID_or_CPG_or_Name->clear();
    ui->line_ID_or_CPG_or_Name->setFocus();
}
