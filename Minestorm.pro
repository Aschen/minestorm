
QT       += core gui

CONFIG+=C++11

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
    server/Carre.cpp

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
    server/Carre.hh

FORMS    +=

INCLUDEPATH += $$PWD/shared
INCLUDEPATH += $$PWD/server
INCLUDEPATH += $$PWD/client 
