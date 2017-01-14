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
    Client_Update.cpp

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
    Client_Update.h

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
    Client_Update.ui

DISTFILES += \
    resources/emote-love.png \
    resources/face-angel.png \
    resources/face-angry.png \
    resources/face-devilish.png \
    resources/face-embarrassed.png \
    resources/face-kiss.png \
    resources/face-monkey.png \
    resources/face-plain.png \
    resources/face-raspberry.png \
    resources/face-sad.png \
    resources/face-smile-big.png \
    resources/face-smile.png \
    resources/face-surprise.png \
    resources/face-wink.png \
    resources/face-worried.png \
    resources/DB11-model2.png \
    TODO \
    Create_Database.sql \
    resources/Translations/Oficina_en_US.ts \
    Oficina_en_US.qm

RESOURCES += \
    resources/images.qrc \
    resources/translations.qrc

TRANSLATIONS += \
    resources/translations/Oficina_en_US.ts \
    resources/translations/Oficina_pt_BR.ts
