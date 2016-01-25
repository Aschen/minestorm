#ifndef MENU_HH
# define MENU_HH

# include <QWidget>

class Display;
/**
 * @brief La class GameBoard définit un widget permettant l'affichage d'un
 * jeu. Elle gère également les évènements souris et clavier
 */
class Menu : public QWidget
{
    Q_OBJECT
private:
    Display *_display;

public:
    explicit Menu(Display *display, QWidget *parent = 0);

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

#endif // MENU_HH
