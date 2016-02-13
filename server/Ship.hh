#ifndef SHIP_HH
# define SHIP_HH


# include <QRect>
# include "QImage"
# include "Entity.hh"
# include "Minestorm.hh"
# include "Projectile.hh"

class Ship : public Entity
{

public:
    enum Rotation
    {
        NONE = 0,
        LEFT = 1,
        RIGHT = 2
    };


private:
    quint32         _vie;
    quint32         _shipNumber;
    qint32          _tempo;
    quint32         _score;
    bool            _scoreChanged;
    bool            _livesChanged;
    bool            _shield;
    Rotation        _rotation;

    bool            _goingUp;

public:
    //Constructeurs
    Ship(const QPointF &position, qint32 shipNumber);

    void            addScore(quint32 score);
    bool            changeLife(qint32 change);
    void            grantShield();
    bool            removeShield();
    QSharedPointer<Entity>  shot();
    void            rotateShip();

    //Getter & Setter
    quint32         vie() const;
    void            setVie(quint32 vie);
    QRect           rect() const;
    void            setRect(const QRect &rect);
    quint32         shipNumber() const;
    void            shipNumber(quint32 shipNumber);
    void            score(quint32 score);
    quint32         score() const;
    bool            scoreChanged();
    bool            livesChanged();
    bool            haveShield();
    Rotation        rotation() const;
    void            setRotation(Rotation rotation);
    bool            goingUp();
    void            goingUp(bool value);


    // Entity interface
public:
    bool            makeEntityMove() override;
    QPointF         center() const override;
};

#endif // SHIP_HH
