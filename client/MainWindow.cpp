#include <QVBoxLayout>
#include <QLabel>
#include "MainWindow.hh"
#include "Controller.hh"
#include "GameBoard.hh"

MainWindow::MainWindow(Display *display, QWidget *parent)
    : QMainWindow(parent)
{
    auto window = new QWidget(this);
    auto controller = new Controller(display, window);
    auto gameboard = new GameBoard(display, window);
    auto layout = new QVBoxLayout;

    gameboard->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);

    layout->addWidget(gameboard);
    layout->addWidget(controller);

    window->setLayout(layout);
    setObjectName("MainWindow");
    setCentralWidget(window);

    setStyleSheet("QMainWindow#MainWindow { background-image: url(images/background.jpg)  no-repeat center center fixed; }");
    show();
}

MainWindow::~MainWindow()
{
}
