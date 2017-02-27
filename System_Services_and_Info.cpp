#include "System_Services_and_Info.h"

#include "qsqltablemodel.h"
#include "qsqlquery.h"
#include "qsqlerror.h"
#include "qmessagebox.h"
#include "QDebug"
#include "QDate"

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

bool System_Services_and_Info::Check_Text_Size(int size_limit)
{
    /*if (ui->txt_Full_Description->toPlainText().length() > 1000)
    {
        QString fullserviceDescription = ui->txt_Full_Description->toPlainText();
        fullserviceDescription.chop(fullserviceDescription.length() - 1000); // Cut off at 500 characters
        ui->txt_Full_Description->setPlainText(fullserviceDescription); // Reset text

        // This code just resets the cursor back to the end position
        // If you don't use this, it moves back to the beginning.
        // This is helpful for really long text edits where you might
        // lose your place.
        QTextCursor cursor = ui->txt_Full_Description->textCursor();
        cursor.setPosition(ui->txt_Full_Description->document()->characterCount() - 1);
        ui->txt_Full_Description->setTextCursor(cursor);

        // This is your "action" to alert the user. I'd suggest something more
        // subtle though, or just not doing anything at all.
        QMessageBox::warning(this, tr("Error!"), tr("Keep the Part description smaller then 500 chars."));
    }*/
     qDebug() << size_limit;
     qInfo() << "abcdefghijklmno" - 51;
     return true;
}
