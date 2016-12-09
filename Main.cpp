#include "Main_Window.h"
#include "QApplication"
#include "QtSql"
#include "QtDebug"
#include "QMessageBox"
#include "Database.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Oficina");
    QApplication::setApplicationVersion("0.1");

    QApplication a(argc, argv);
    Main_Window w;
    w.show();

    return a.exec();
}
