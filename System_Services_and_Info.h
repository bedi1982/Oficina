#ifndef SYSTEM_SERVICES_H
#define SYSTEM_SERVICES_H

#endif // SYSTEM_SERVICES_H

#include <QDialog>

namespace Ui {
class System_Services;
}

class System_Services : public QDialog
{
    Q_OBJECT

public:
    double Get_Current_Hour_Cost();
};
