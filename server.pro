TEMPLATE = lib
TARGET = server
CONFIG += dll
QT += core network widgets
QT += remoteobjects
QT += androidextras

SOURCES += \
    network/budplogger.cpp \
    network/gpsinterface.cpp \
    network/networkhandler.cpp \
    server.cpp

HEADERS += \
    network/budplogger.h \
    network/gpsinterface.h \
    network/networkhandler.h
