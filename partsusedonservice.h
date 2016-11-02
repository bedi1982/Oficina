#ifndef PARTSUSEDONSERVICE_H
#define PARTSUSEDONSERVICE_H

#include <QDialog>

namespace Ui {
class partsUsedOnService;
}

class partsUsedOnService : public QDialog
{
    Q_OBJECT

public:
    explicit partsUsedOnService(QWidget *parent = 0);
    ~partsUsedOnService();

private:
    Ui::partsUsedOnService *ui;
};

#endif // PARTSUSEDONSERVICE_H
