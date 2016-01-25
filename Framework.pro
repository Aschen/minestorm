
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
    Core.cpp

HEADERS  += \
    DrawableObject.hh \
    Display.hh \
    MainWindow.hh \
    Controller.hh \
    Minestorm.hh \
    GameBoard.hh \
    GameProxy.hh \
    Core.hh

FORMS    +=
