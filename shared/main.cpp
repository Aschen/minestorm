#include <QSize>
#include <QApplication>

#include "MainWindow.hh"
#include "GameProxy.hh"
#include "Display.hh"
#include "Core.hh"

#include "Server.hh"
#include "Client.hh"

#include "Message.hh"

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
//    Message     msg("1 21 42");
//    qDebug() << msg.typeStr() << " x: " << msg.point()->x() << " y: " << msg.point()->y();

//    Message     msg2("3 42");
//    qDebug() << msg2.typeStr() << "keyCode: " << msg2.keyCode();

//    Message     msg3("7 3 2 42 21 84 48 3 12 21 34 43 56 65 1 23 22");
//    qDebug() << msg3.typeStr() << "size: " << msg3.objects()->size();
//    qDebug() << msg3.objects()->at(0).at(0).y();
//    qDebug() << sizeof(int);
//    return 0;

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
