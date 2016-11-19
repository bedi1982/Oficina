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
    partsselectionfromlist.cpp \
    editclient.cpp \
    stockcontrol.cpp \
    setworkhourcost.cpp \
    createservicedescription.cpp \
    updatedservicedescription.cpp \
    manul.cpp

HEADERS  += mainwindow.h \
    addpart.h \
    addservice.h \
    addclient.h \
    addclientcar.h \
    about.h \
    clientinfo.h \
    database.h \
    partsselectionfromlist.h \
    editclient.h \
    stockcontrol.h \
    setworkhourcost.h \
    createservicedescription.h \
    updatedservicedescription.h \
    manul.h

FORMS    += mainwindow.ui \
    addpart.ui \
    addservice.ui \
    addclient.ui \
    addclientcar.ui \
    about.ui \
    clientinfo.ui \
    partsselectionfromlist.ui \
    editclient.ui \
    stockcontrol.ui \
    setworkhourcost.ui \
    createservicedescription.ui \
    updatedservicedescription.ui \
    manul.ui

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
