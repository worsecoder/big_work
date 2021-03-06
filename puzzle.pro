#-------------------------------------------------
#
# Project created by QtCreator 2018-12-09T14:02:24
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = puzzle
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    utils.cpp \
    node.cpp \
    open.cpp \
    close.cpp \
    solver.cpp \
    welcome.cpp \
    setlevel.cpp \
    scene.cpp \
    savepic.cpp \
    saveprogress.cpp \
    loadprogress.cpp \
    bmpreader.cpp

HEADERS += \
        mainwindow.h \
    utils.h \
    node.h \
    open.h \
    close.h \
    solver.h \
    welcome.h \
    setlevel.h \
    scene.h \
    savepic.h \
    saveprogress.h \
    loadprogress.h \
    musicplayer.h \
    bmpreader.h

FORMS += \
        mainwindow.ui \
    welcome.ui \
    setlevel.ui \
    savepic.ui \
    saveprogress.ui \
    loadprogress.ui

RESOURCES += \
    resource.qrc

CONFIG+= resources_big
