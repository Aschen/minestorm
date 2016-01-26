#include <QSize>
#include <QApplication>

#include "MainWindow.hh"
#include "GameProxy.hh"
#include "Display.hh"
#include "Core.hh"

#include "Server.hh"
#include "Client.hh"

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
//    Display         display(QSize(400, 400));
//    Core            core(20);
//    GameProxy       proxy(&core, &display);
//    MainWindow      w(&display);

//    return a.exec();
    QMainWindow         window;

    window.show ();

    QString     arg(argv[1]);

    if (arg == "server")
    {
        Server      *srv = new Server(4242);

        srv->start();
    }
    else
    {
        Client      *cli = new Client("127.0.0.1", 4242);

        cli->connectServer();
    }

    return a.exec();
}
