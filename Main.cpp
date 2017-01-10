#include "Main_Window.h"
#include "QApplication"
#include "QtSql"
#include "QtDebug"
#include "QMessageBox"
#include "Database.h"

#include "QTranslator"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Oficina");
    QApplication::setApplicationVersion("0.1");

    QApplication a(argc, argv);

    QTranslator translation;
    QFile file("Oficina_en_US.qm");

    if(file.exists()){
        qDebug() << "existe";
        translation.load("Oficina_en_US.qm");
        a.installTranslator(&translation);
    }else{
        qDebug() << "no existe";
    }

    Main_Window w;
    w.show();

    return a.exec();
}
