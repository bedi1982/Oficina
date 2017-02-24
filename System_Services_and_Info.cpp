#include "System_Services_and_Info.h"

#include "qsqltablemodel.h"
#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qmessagebox.h"
#include "QDate"

double System_Services_and_Info::Get_Current_Hour_Cost(){
    //just set current value in the spinbox//
    QSqlQuery Get_Current_Hour_Cost;
    Get_Current_Hour_Cost.prepare("SELECT HourCost FROM HourCost ORDER BY HourCost_id DESC LIMIT 1");

    if (Get_Current_Hour_Cost.exec() == false){
        QMessageBox::critical(this, tr("Error!"), Get_Current_Hour_Cost.lastError().text() + "class: double System_Services::Get_Current_Hour_Cost()");
    }else{
        while(Get_Current_Hour_Cost.next())
        {
            return Get_Current_Hour_Cost.value(0).toDouble();
        }
    }
    return 0;
}

QString System_Services_and_Info::getSystem_Version() const
{
    return System_Version;
}

QString System_Services_and_Info::get_Current_Date() const
{
    QDate QDate;
    return QDate.currentDate().toString();
}
