
QT       += core gui

CONFIG+=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minestorme
TEMPLATE = app


SOURCES += server/Core.cpp \
    client/Controller.cpp \
    client/Display.cpp \
    client/GameBoard.cpp \
    client/MainWindow.cpp \
    shared/DrawableObject.cpp \
    shared/GameProxy.cpp \
    shared/Mine.cpp\
    shared/main.cpp \
    shared/Ship.cpp \
    server/Entity.cpp

HEADERS  += server/Core.hh \
    client/Controller.hh \
    client/Display.hh \
    client/GameBoard.hh \
    client/MainWindow.hh \
    shared/DrawableObject.hh \
    shared/GameProxy.hh \
    shared/Minestorm.hh\
    shared/Mine.hh \
    shared/Ship.hh \
    server/Entity.hh

FORMS    +=

INCLUDEPATH += $$PWD/shared
INCLUDEPATH += $$PWD/server
INCLUDEPATH += $$PWD/client 
