#include "System_Services_and_Info.h"

#include "qsqltablemodel.h"
#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qmessagebox.h"
#include "QDebug"
#include "QDate"

static bool Is_New_Client = false;

double System_Services_and_Info::Get_Current_Hour_Cost(){
    //just set current value in the spinbox//
    QSqlQuery Get_Current_Hour_Cost;
    Get_Current_Hour_Cost.prepare("SELECT HourCost FROM HourCost ORDER BY HourCost_id DESC LIMIT 1");

    if (Get_Current_Hour_Cost.exec() == false){
        qWarning() << " ERROR IN CLASS: double System_Services::Get_Current_Hour_Cost()";
    }else{
        while(Get_Current_Hour_Cost.next())
        {
            return Get_Current_Hour_Cost.value(0).toDouble();
        }
    }
    return 0;
}

QString System_Services_and_Info::get_Current_Date()
{
    return QDate::currentDate().toString();
}

QString System_Services_and_Info::get_System_Version()
{
    return "Oficina - 0.2 HackWeek";
}

QString System_Services_and_Info::get_System_About()
{
    return tr("Software to manage mechanical workshop services.\n"
                                    "\n"
                                    "Author: Sergio Rafael Lemke <bedi.com@gmail.com>\n");

}

QString System_Services_and_Info::Check_Text_Size(int size_limit, QString Entered_Text)
{
    int Overflowed_Chars = Entered_Text.length() - size_limit;
    Entered_Text.chop(Overflowed_Chars);
    return Entered_Text;
}

bool System_Services_and_Info::get_is_New_Client()
{
    return Is_New_Client;
}

void System_Services_and_Info::set_is_New_Client(bool value)
{
    Is_New_Client = value;
}
