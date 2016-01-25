#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QTimer>
#include <QSize>
class QPainter;
class QRect;

/**
 * @brief La classe Game est une classe abstraite représentant base d'un jeu.
 *  Elle fournit les services de base pour controler un jeu :
 *  - start/pause/reset
 *  - gestion des évènements souris
 *  - gestion des évènements clavier
 *  - gestion de l'affichage
 */
class Game: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Game contruit un jeu
     * @param size taille de la grille de jeu
     * @param parent
     */
    Game(const QSize &size,QObject *parent);
    /**
     * @brief start démarre le jeu
     */
    void start();
    /**
     * @brief pause met le jeu en pause
     */
    void pause();
    /**
     * @brief reset stop le jeu et le réinitialise
     */
    void reset();

    /**
     * @brief setSpeed modifie la vitesse d'exécution du jeu
     * @param speed
     */
    void setSpeed( int speed );
    /**
     * @brief speed retourne la vitesse d'exécution du jeu
     * @return
     */
    int speed() const ;

    /**
     * @brief size retourne la taille du jeu
     * @return
     */
    const QSize &size() const;

    /**
     * @brief draw appelée pour afficher le jeu. Cette méthode doit être
     * implémentée par les classes dérivées
     * @param painter context d'affichage voir [la documentation Qt](http://doc.qt.io/qt-5/qpainter.html)
     * @param size taille de la zone dans laquelle peindre le jeu
     */
    virtual void draw(QPainter &painter, QRect &size) = 0;
    /**
     * @brief mousePressed appélée quand l'utilisateur click dans le jeu
     * @param x coordonnée x dans le jeu de la souris lors du click
     * @param y coordonnée y dans le jeu de la souris lors du click
     * @see size()
     */
    virtual void mousePressed( int x, int y) = 0;

    /**
     * @brief mouseReleased appelée quand l'utilisateur relache le bouton de la souris
     * @param x coordonnée x dans le jeu de la souris
     * @param y coordonnée y dans le jeu de la souris
     */
    virtual void mouseReleased( int x, int y) = 0;
    /**
     * @brief mouseReleased appelée quand l'utilisateur déplacé la souris
     * @param x coordonnée x dans le jeu de la souris
     * @param y coordonnée y dans le jeu de la souris
     */
    virtual void mouseMoved(int x, int y) = 0;

    /**
     * @brief keyPressed  appélée quand l'utilisateur presse une touche
     * @param key code de la touche. Tous les codes sont disponible dans [la documentation Qt](http://doc.qt.io/qt-5/qt.html#Key-enum)
     *
     */
    virtual void keyPressed( int key ) = 0;
    /**
     * @brief keyReleased  appélée quand l'utilisateur relache une touche
     * @param key code de la touche. Tous les codes sont disponible dans [la documentation Qt](http://doc.qt.io/qt-5/qt.html#Key-enum)
     *
     */
    virtual void keyReleased( int key ) = 0;

    /**
     * @brief isRunning retourne true si le jeu est lancé
     * @return
     */
    bool isRunning() const;
protected:
    /**
     * @brief step fait avancer le jeu d'une itération
     */
    virtual void step() = 0;
    /**
     * @brief initialize initialise ou réinitialise le jeu
     */
    virtual void initialize() = 0;

signals:
    void changed();

private slots:

    void update();
private:
    QTimer _timer;
    bool _isRunning;
    int _speed;
    QSize _size;
};

#endif // GAME_H
