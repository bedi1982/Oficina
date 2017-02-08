#include "Main_Window.h"
#include "QApplication"

#include "QDebug"

//Translations//
#include "QTranslator"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Oficina");
    QApplication::setApplicationVersion("0.1.1");

    QApplication a(argc, argv);

    QTranslator translation;
    QFile file(":/translations/Oficina_pt_BR.qm-DISABLED");

    if(file.exists()){
        qDebug() << "Testing tranlations: exist";
        translation.load(":/translations/Oficina_pt_BR.qm");
        a.installTranslator(&translation);
    }else{
        qDebug() << "Testing tranlations: no exists";
    }

    Main_Window w;
    w.show();

    return a.exec();
}
