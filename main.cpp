#include "MainWindow.hh"
#include "Display.hh"

#include <QSize>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    Display         display(QSize(400,400));
    MainWindow      w(&display);

    return a.exec();
}
