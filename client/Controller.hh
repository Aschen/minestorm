#ifndef CONTROLLER_HH
# define CONTROLLER_HH

# include <QWidget>
# include <QLineEdit>

# include "CoreRunner.hh"

class Display;

/**
 * @brief La classe Controller définit une widget permettant le controle d'un jeu
 */
class Controller : public QWidget
{
    Q_OBJECT
private:
    Display     *_display;
    QLineEdit   *_inputHost;
    QLineEdit   *_inputPseudo;
    QSharedPointer<CoreRunner>  _coreRunner;

public:
    Controller(Display *display, QWidget *parent = nullptr);

private slots:
    void        startNewGame();
    void        joinGame();
    void        exitGame();

};

#endif // CONTROLLER_HH
