#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
class Game;
/**
 * @brief La classe Controller définit une widget permettant le controle d'un jeu
 */
class Controller:public QWidget
{
    Q_OBJECT
public:
    Controller(Game *game, QWidget *parent = nullptr);

private slots:
    void start();
    void pause();
    void reset();
    void changeSpeed( int speed );

private:
    Game *_game;
};

#endif // CONTROLLER_H
