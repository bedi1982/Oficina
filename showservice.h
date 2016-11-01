#ifndef SHOWSERVICE_H
#define SHOWSERVICE_H

#include <QDialog>

namespace Ui {
class showService;
}

class showService : public QDialog
{
    Q_OBJECT

public:
    explicit showService(QWidget *parent = 0);
    ~showService();

private:
    Ui::showService *ui;
};

#endif // SHOWSERVICE_H
