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
    Client_Edit.cpp \
    Man_Page.cpp \
    Stock_Parts_Selection.cpp \
    Service_Update_Description.cpp \
    Config_Set_Hour_Cost.cpp \
    Stock_Control.cpp \
    Database.cpp \
    Main.cpp \
    Main_Window.cpp \
    Client_Services_History.cpp

HEADERS  += \
    About.h \
    Client_Add.h \
    Client_Add_Car.h \
    Stock_Add_Part.h \
    Client_Add_Service.h \
    Service_Create_Description.h \
    Client_Edit.h \
    Man_Page.h \
    Stock_Parts_Selection.h \
    Service_Update_Description.h \
    Config_Set_Hour_Cost.h \
    Stock_Control.h \
    Database.h \
    Main_Window.h \
    Client_Services_History.h

FORMS    += \
    About.ui \
    Client_Add.ui \
    Client_Add_Car.ui \
    Stock_Add_Part.ui \
    Client_Add_service.ui \
    Service_Create_Description.ui \
    Client_Edit.ui \
    Man_Page.ui \
    Stock_Parts_Selection.ui \
    Service_Update_Description.ui \
    Config_Set_Hour_Cost.ui \
    Stock_Control.ui \
    Main_Window.ui \
    Client_Services_History.ui

DISTFILES += \
    database_creation \
    resources/emote-love.png \
    resources/face-angel.png \
    resources/face-angry.png \
    resources/face-cool.png \
    resources/face-crying.png \
    resources/face-devilish.png \
    resources/face-embarrassed.png \
    resources/face-glasses.png \
    resources/face-kiss.png \
    resources/face-laugh.png \
    resources/face-monkey.png \
    resources/face-plain.png \
    resources/face-raspberry.png \
    resources/face-sad.png \
    resources/face-sick.png \
    resources/face-smile-big.png \
    resources/face-smile.png \
    resources/face-smirk.png \
    resources/face-surprise.png \
    resources/face-tired.png \
    resources/face-uncertain.png \
    resources/face-wink.png \
    resources/face-worried.png \
    resources/DB11-model2.png \
    TODO

RESOURCES += \
    resources/images.qrc
