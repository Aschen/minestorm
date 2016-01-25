#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;
/**
 * @brief La classe MainWindow crée un widget contenant un controller et un gameboard pour le game
 * donné
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Game *game,QWidget *parent = 0);
    ~MainWindow();

private:
};

#endif // MAINWINDOW_H
