
QT       += core gui

CONFIG+=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TD5
TEMPLATE = app


SOURCES += main.cpp\
    DrawableObject.cpp \
    Display.cpp \
    MainWindow.cpp \
    Controller.cpp \
    GameBoard.cpp \
    GameProxy.cpp \
    server/Core.cpp \
    client/Controller.cpp \
    client/Display.cpp \
    client/GameBoard.cpp \
    client/MainWindow.cpp \
    shared/DrawableObject.cpp \
    shared/GameProxy.cpp \
    shared/main.cpp

HEADERS  += \
    DrawableObject.hh \
    Display.hh \
    MainWindow.hh \
    Controller.hh \
    Minestorm.hh \
    GameBoard.hh \
    GameProxy.hh \
    server/Core.hh \
    client/Controller.hh \
    client/Display.hh \
    client/GameBoard.hh \
    client/MainWindow.hh \
    shared/DrawableObject.hh \
    shared/GameProxy.hh \
    shared/Minestorm.hh

FORMS    +=
