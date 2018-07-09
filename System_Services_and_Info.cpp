#include "System_Services_and_Info.h"

#include "qsqltablemodel.h"
#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qmessagebox.h"
#include "QDebug"
#include "QDate"

static bool Is_New_Client = false;
static int Logged_Func = -1;

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
    return "Oficina - HackWeek.2018";
}

QString System_Services_and_Info::get_System_About()
{
    return tr("Software to manage mechanical workshop services.\n"
                                    "\n"
                                    "Author: Sergio Rafael Lemke <srlemke@protonmail.com>\n");

}

QString System_Services_and_Info::Check_Text_Size(int size_limit, QString Entered_Text)
{
    int Overflowed_Chars = Entered_Text.length() - size_limit;
    Entered_Text.chop(Overflowed_Chars);
    return Entered_Text;
}

void System_Services_and_Info::set_is_New_or_Updated_Client(bool Is_New)
{
    Is_New_Client = Is_New;
}

bool System_Services_and_Info::get_is_New_or_Updated_Client()
{
    return Is_New_Client;
}

int System_Services_and_Info::get_Logged_Func(){
    return Logged_Func;
}

void System_Services_and_Info::set_Logged_func(int func_id){
    Logged_Func = func_id;
}
