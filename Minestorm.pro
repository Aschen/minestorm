QT      +=  multimedia
QMAKE_CXX   =   clang++
QMAKE_CC    =   clang

QT      +=  core gui network multimedia

CONFIG  +=  C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multistorm
TEMPLATE = app


SOURCES += server/Core.cpp \
    client/Controller.cpp \
    client/Display.cpp \
    client/GameBoard.cpp \
    client/MainWindow.cpp \
    shared/main.cpp \
    server/Mine.cpp\
    server/Ship.cpp \
    server/Entity.cpp \
    server/Server.cpp \
    client/Client.cpp \
    server/Worker.cpp \
    shared/BaseSocket.cpp \
    shared/MessageBase.cpp \
    shared/MessageMouse.cpp \
    shared/MessageObjects.cpp \
    server/CoreRunner.cpp \
    shared/MessageKey.cpp \
    client/Element.cpp \
    client/Images.cpp \
    server/Collision.cpp \
    server/Projectile.cpp \
    server/Player.cpp \
    server/Players.cpp \
    client/PlayerInfos.cpp \
    client/PlayersInfos.cpp \
    shared/MessagePlayersInfos.cpp \
    client/FpsCounter.cpp \
    shared/MessagePseudo.cpp

HEADERS  += server/Core.hh \
    client/Controller.hh \
    client/Display.hh \
    client/GameBoard.hh \
    client/MainWindow.hh \
    shared/Minestorm.hh\
    server/Mine.hh \
    server/Ship.hh \
    server/Entity.hh \
    server/Server.hh \
    client/Client.hh \
    server/Worker.hh \
    shared/BaseSocket.hh \
    shared/MessageBase.hh \
    shared/MessageMouse.hh \
    shared/MessageObjects.hh \
    server/CoreRunner.hh \
    shared/MessageKey.hh \
    client/Element.hh \
    client/Images.hh \
    server/Collision.hh \
    server/Projectile.hh \
    server/Player.hh \
    server/Players.hh \
    client/PlayerInfos.hh \
    client/IDrawable.hh \
    client/PlayersInfos.hh \
    shared/MessagePlayersInfos.hh \
    client/FpsCounter.hh \
    shared/MessagePseudo.hh

FORMS    +=

INCLUDEPATH += $$PWD/shared
INCLUDEPATH += $$PWD/server
INCLUDEPATH += $$PWD/client 
