QMAKE_CXX   =   clang++
QMAKE_CC    =   clang

QT      +=  core gui network testlib

CONFIG  +=  C++11
CONFIG  +=  testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minestorm
TEMPLATE = app


SOURCES += server/Core.cpp \
    client/Controller.cpp \
    client/Display.cpp \
    client/GameBoard.cpp \
    client/MainWindow.cpp \
    shared/GameProxy.cpp \
    shared/main.cpp \
    server/Mine.cpp\
    server/Ship.cpp \
    server/Entity.cpp \
    server/Carre.cpp \
    server/Server.cpp \
    client/Client.cpp \
    server/Worker.cpp \
    shared/BaseSocket.cpp \
    test/TestMessage.cpp \
    shared/test.cpp \
    shared/MessageBase.cpp \
    shared/MessageMouse.cpp \
    shared/MessageObjects.cpp

HEADERS  += server/Core.hh \
    client/Controller.hh \
    client/Display.hh \
    client/GameBoard.hh \
    client/MainWindow.hh \
    shared/GameProxy.hh \
    shared/Minestorm.hh\
    server/Mine.hh \
    server/Ship.hh \
    server/Entity.hh \
    server/Carre.hh \
    server/Server.hh \
    client/Client.hh \
    server/Worker.hh \
    shared/BaseSocket.hh \
    test/TestMessage.hh \
    shared/MessageBase.hh \
    shared/MessageMouse.hh \
    shared/MessageObjects.hh

FORMS    +=

INCLUDEPATH += $$PWD/shared
INCLUDEPATH += $$PWD/server
INCLUDEPATH += $$PWD/client 
