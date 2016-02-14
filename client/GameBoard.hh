#ifndef GAMEBOARD_HH
# define GAMEBOARD_HH

# include <QWidget>
# include <QTimer>
# include <QPainter>
# include <QColor>
# include <QMouseEvent>

# include "Minestorm.hh"
# include "Display.hh"

class Display;
/**
 * @brief La class GameBoard définit un widget permettant l'affichage d'un
 * jeu. Elle gère également les évènements souris et clavier
 */
class GameBoard : public QWidget
{
    Q_OBJECT
private:
    Display     *_display;
    bool        _acceptEvent;
    QTimer      _timer;

public:
    explicit GameBoard(Display *display, QWidget *parent = 0);

protected:
    void        paintEvent(QPaintEvent *);
    void        mousePressEvent(QMouseEvent * event);
    void        keyPressEvent(QKeyEvent * event);
    void        keyReleaseEvent(QKeyEvent * event);
};

#endif // GAMEBOARD_HH
