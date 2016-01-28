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

    QString     arg(argv[1]);

    if (arg == "srv")
    {
        Core            *core = new Core(20);
        return a.exec();
    }
    else
    {
        Display         display(QSize(400, 400));
        MainWindow      w(&display);
        return a.exec();
    }


//    QMainWindow         window;

//    window.show ();

//    if (arg == "server")
//    {
//        Server      *srv = new Server(4242);

//        srv->start();
//    }
//    else
//    {
//        Client      *cli = new Client("127.0.0.1", 4242);

//        cli->start();
//        cli->sendMessage("Hello server !");
//    }

//    return a.exec();
}
