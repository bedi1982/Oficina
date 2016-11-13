#ifndef UPDATEDSERVICEDESCRIPTION_H
#define UPDATEDSERVICEDESCRIPTION_H

#include <QDialog>

namespace Ui {
class Updatedservicedescription;
}

class Updatedservicedescription : public QDialog
{
    Q_OBJECT

public:
    explicit Updatedservicedescription(QWidget *parent = 0);
    ~Updatedservicedescription();
    void SetDescription();
    void EnableDescriptionUpdate();
    QString serviceID;

    QString getServiceID() const;
    void setServiceID(const QString &value);

private slots:
    void on_btn_salvar_clicked();

    void on_txt_FullDescription_textChanged();

private:
    Ui::Updatedservicedescription *ui;
};

#endif // UPDATEDSERVICEDESCRIPTION_H
