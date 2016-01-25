#include "mainwindow.h"
#include "controller.h"
#include "gameboard.h"
#include <QVBoxLayout>
MainWindow::MainWindow(Game *game,QWidget *parent) :
    QMainWindow(parent)
{

    auto window = new QWidget(this);
    auto controller = new Controller(game, window);
    auto gameboard = new GameBoard(game,window);
    gameboard->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);


    auto layout = new QVBoxLayout;
    layout->addWidget(gameboard);
    layout->addWidget(controller);

    window->setLayout(layout);
    setCentralWidget(window);
    show();

}

MainWindow::~MainWindow()
{

}
