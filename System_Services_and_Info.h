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
    double Get_Current_Hour_Cost();
    QString System_Version = "Oficina - 0.2 HackWeek";

    QString getSystem_Version() const;
    QString get_Current_Date() const;
};
