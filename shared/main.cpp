#include <QSize>
#include <QApplication>
#include <QSharedPointer>

#include "MainWindow.hh"
#include "Display.hh"
#include "Core.hh"

#include "Server.hh"
#include "Client.hh"

void        runTests();

int main(int argc, char *argv[])
{
    QString     arg(argv[1]);

    if (arg == "srv")
    {
        QApplication    a(argc, argv);
        Core            *core = new Core;

        core->startGame();

        return a.exec();
    }
    else
    {
        QApplication    a(argc, argv);
        Display         display(QSize(SCREEN_SIZE, SCREEN_SIZE));
        MainWindow      w(&display);

        return a.exec();
    }
//    if (arg == "test")
//    {
//        runTests();

//        return 0;
//    }
//    else
//    {
//        QApplication    app(argc, argv);
//        Display         display(QSize(SCREEN_SIZE, SCREEN_SIZE));
//        MainWindow      window(&display);

//        return app.exec();
//    }
}
