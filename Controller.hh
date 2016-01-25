#ifndef CONTROLLER_HH
# define CONTROLLER_HH

# include <QWidget>

class Display;

/**
 * @brief La classe Controller définit une widget permettant le controle d'un jeu
 */
class Controller : public QWidget
{
    Q_OBJECT
private:
    Display *_display;

public:
    Controller(Display *display, QWidget *parent = nullptr);

private slots:
    void    start();
    void    pause();
    void    reset();

};

#endif // CONTROLLER_HH
