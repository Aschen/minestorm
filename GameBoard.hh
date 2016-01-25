#ifndef GAMEBOARD_HH
# define GAMEBOARD_HH

# include <QWidget>

class Display;
/**
 * @brief La class GameBoard définit un widget permettant l'affichage d'un
 * jeu. Elle gère également les évènements souris et clavier
 */
class GameBoard : public QWidget
{
    Q_OBJECT
private:
    Display *_display;

public:
    explicit GameBoard(Display *display, QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // GAMEBOARD_HH
