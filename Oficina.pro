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


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    addpart.cpp \
    addservice.cpp \
    addclient.cpp \
    addclientcar.cpp \
    about.cpp \
    clientinfo.cpp \
    clientbundle.cpp \
    realizedserviceinfo.cpp \
    partsusedonservice.cpp

HEADERS  += mainwindow.h \
    addpart.h \
    addservice.h \
    addclient.h \
    addclientcar.h \
    about.h \
    clientinfo.h \
    clientbundle.h \
    database.h \
    realizedserviceinfo.h \
    partsusedonservice.h

FORMS    += mainwindow.ui \
    addpart.ui \
    addservice.ui \
    addclient.ui \
    addclientcar.ui \
    about.ui \
    clientinfo.ui \
    realizedserviceinfo.ui \
    partsusedonservice.ui

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
    resources/face-worried.png

RESOURCES += \
    resources/images.qrc
