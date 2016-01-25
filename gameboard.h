#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
class Game;
/**
 * @brief La class GameBoard définit un widget permettant l'affichage d'un
 * jeu. Elle gère également les évènements souris et clavier
 */
class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(Game *game,QWidget *parent = 0);

signals:

public slots:


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent ( QMouseEvent * event );
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Game *_game;
};

#endif // GAMEBOARD_H
