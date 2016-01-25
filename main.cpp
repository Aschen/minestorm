#include "mainwindow.h"
#include "Core.hh"

#include <QSize>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Core game(QSize(400,400));
    MainWindow w(&game);
    return a.exec();
}
