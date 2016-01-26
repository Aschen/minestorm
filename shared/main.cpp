#include <QSize>
#include <QApplication>

#include "MainWindow.hh"
#include "GameProxy.hh"
#include "Display.hh"
#include "Core.hh"

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    Display         display(QSize(400, 400));
    Core            core(20);
    GameProxy       proxy(&core, &display);
    MainWindow      w(&display);

    return a.exec();
}
