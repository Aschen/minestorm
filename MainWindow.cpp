#include <QVBoxLayout>
#include "MainWindow.hh"
#include "Controller.hh"
#include "Menu.hh"

MainWindow::MainWindow(Display *display, QWidget *parent)
    : QMainWindow(parent)
{
    auto window = new QWidget(this);
    auto controller = new Controller(display, window);
    auto menu = new Menu(display, window);
    auto layout = new QVBoxLayout;

    menu->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding);

    layout->addWidget(menu);
    layout->addWidget(controller);

    window->setLayout(layout);
    setCentralWidget(window);
    show();
}

MainWindow::~MainWindow()
{
}
