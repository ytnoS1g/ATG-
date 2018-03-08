#-------------------------------------------------
#
# Project created by QtCreator 2018-02-15T09:35:21
#
#-------------------------------------------------

QT       += network
QT       += serialport
QT       += core

QT       -= gui

TARGET = LwComStreamer
TEMPLATE = lib

DEFINES += LWCOMSTREAMER_LIBRARY

SOURCES += \
    lwcomserialstreamer.cpp \
    lwcomtcpstreamer.cpp \
    main.cpp

HEADERS += lwcomstreamer.h\
        lwcomstreamer_global.h \
    lwcomserialstreamer.h \
    lwcomtcpstreamer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
