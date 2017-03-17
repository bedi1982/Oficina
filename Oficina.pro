#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T20:43:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Oficina
TEMPLATE = app


SOURCES +=\
    About.cpp \
    Client_Add.cpp \
    Client_Add_Car.cpp \
    Stock_Add_Part.cpp \
    Client_Add_Service.cpp \
    Service_Create_Description.cpp \
    Man_Page.cpp \
    Stock_Parts_Selection.cpp \
    Service_Update_Description.cpp \
    Config_Set_Hour_Cost.cpp \
    Stock_Control.cpp \
    Database.cpp \
    Main.cpp \
    Main_Window.cpp \
    Client_Services_History.cpp \
    Client_Update.cpp \
    Stock_Update_Part.cpp \
    Stock_Finances.cpp \
    Employee_Add.cpp \
    Employee_Update.cpp \
    Employee_List.cpp \
    Login.cpp\
    System_Services_and_Info.cpp

HEADERS  += \
    About.h \
    Client_Add.h \
    Client_Add_Car.h \
    Stock_Add_Part.h \
    Client_Add_Service.h \
    Service_Create_Description.h \
    Man_Page.h \
    Stock_Parts_Selection.h \
    Service_Update_Description.h \
    Config_Set_Hour_Cost.h \
    Stock_Control.h \
    Database.h \
    Main_Window.h \
    Client_Services_History.h \
    Client_Update.h \
    Stock_Update_Part.h \
    Stock_Finances.h \
    Employee_Add.h \
    Employee_Update.h \
    Employee_List.h \
    Login.h\
    System_Services_and_Info.h

FORMS    += \
    About.ui \
    Client_Add.ui \
    Client_Add_Car.ui \
    Stock_Add_Part.ui \
    Client_Add_service.ui \
    Service_Create_Description.ui \
    Man_Page.ui \
    Stock_Parts_Selection.ui \
    Service_Update_Description.ui \
    Config_Set_Hour_Cost.ui \
    Stock_Control.ui \
    Main_Window.ui \
    Client_Services_History.ui \
    Client_Update.ui \
    Stock_Update_Part.ui \
    Stock_Finances.ui \
    Employee_Add.ui \
    Employee_Update.ui \
    Login.ui\
    Employee_List.ui

DISTFILES += \
    images/emote-love.png \
    images/face-angel.png \
    images/face-angry.png \
    images/face-cool.png \
    images/face-crying.png \
    images/face-devilish.png \
    images/face-embarrassed.png \
    images/face-glasses.png \
    images/face-kiss.png \
    images/face-laugh.png \
    images/face-monkey.png \
    images/face-plain.png \
    images/face-raspberry.png \
    images/face-sad.png \
    images/face-sick.png \
    images/face-smile-big.png \
    images/face-smile.png \
    images/face-smirk.png \
    images/face-surprise.png \
    images/face-tired.png \
    images/face-uncertain.png \
    images/face-wink.png \
    images/face-worried.png \
    images/DB11-model2.png \
    images/carkey.png \
    images/client_info.png \
    images/emblem-default.png \
    images/emblem-important.png \
    images/hint.png \
    images/service.png \
    images/sport-car.png \
    images/tux.png \
    images/Oficina-0.1.1.png \
    images/Screenshots/Oficina_Add_Client.png \
    images/Screenshots/Oficina_ClientAddCar.png \
    images/Screenshots/Oficina_editing_A_Service.png \
    images/Screenshots/Oficina_HourCost.png \
    images/Screenshots/Oficina_Stock_Control.png \
    images/Screenshots/Oficina-0.1-Alpha_eh_Pouco.png \
    images/Screenshots/Oficina-0.2-HackWeek.png \
    images/Screenshots/Oficina_Stock_AddPart.png \
    po/Oficina_pt_BR.qm \
    po/Oficina_pt_BR.ts \
    Create_Database.sql \
    LICENSE \
    README.md \
    TODO \
    Oficina.Desktop

RESOURCES += \
    images/images.qrc \
    po/Oficina_pt_BR.ts \
    po/Oficina_pt_BR.qm

TRANSLATIONS += \
    po/Oficina_pt_BR.ts \
    po/Oficina_pt_BR.qm
