#include <QSize>
#include <QApplication>
#include <QSharedPointer>

#include "MainWindow.hh"
#include "GameProxy.hh"
#include "Display.hh"
#include "Core.hh"

#include "Server.hh"
#include "Client.hh"

#include "MessageFactory.hpp"

void        runTests();

int main(int argc, char *argv[])
{
    QString     arg(argv[1]);

    if (arg == "srv")
    {
        QApplication    a(argc, argv);
        Core            *core = new Core(20);

        return a.exec();
    }
    else if (arg == "cli")
    {
        QApplication    a(argc, argv);
        Display         display(QSize(400, 400));
        MainWindow      w(&display);

        return a.exec();
    }
    else if (arg == "test")
    {
        runTests();

        return 0;
    }
    else
    {
        qDebug() << "Usage : " << argv[0] << " <cli|srv|test>";

        return 0;
    }
}
