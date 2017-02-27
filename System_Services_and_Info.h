#ifndef SYSTEM_SERVICES_H
#define SYSTEM_SERVICES_H

#endif // SYSTEM_SERVICES_H

#include <QDialog>

namespace Ui {
class System_Services;
}

class System_Services_and_Info : public QDialog
{
    Q_OBJECT

public:
    static double Get_Current_Hour_Cost();
    static QString get_System_Version();
    static QString get_Current_Date();
    static QString Check_Text_Size(int size_limit, QString Entered_Text);
};
