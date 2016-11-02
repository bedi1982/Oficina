#include "mainwindow.h"
#include "QApplication"
#include "QtSql"
#include "QtDebug"
#include "QMessageBox"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Oficina");
    QApplication::setApplicationVersion("0.1");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
