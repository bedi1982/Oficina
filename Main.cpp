#include "Main_Window.h"
#include "QApplication"
#include "System_Services_and_Info.h"

#include "QDebug"

//Translations//
#include "QTranslator"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Oficina");
    QApplication::setApplicationVersion(System_Services_and_Info::get_System_Version());

    QApplication a(argc, argv);

//    //Translations are working - disabled for now//
//    QTranslator translation;
//    QFile file(":po/Oficina_pt_BR.qm");

//    if(file.exists()){
//        translation.load(":po/Oficina_pt_BR.qm");
//        a.installTranslator(&translation);
//        qDebug() << "Test tranlations: Found!";
//    }else{
//        qDebug() << "Test tranlations: Not Found";
//    }

    Main_Window w;
    w.show();

    return a.exec();
}
