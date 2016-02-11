#ifndef SHIP_HH
# define SHIP_HH


# include <QRect>
# include "QImage"
# include "Entity.hh"
# include "Minestorm.hh"

class Ship : public Entity
{
private:
    quint32         _vie;
    quint32         _shipNumber;
    qint32          _tempo;
    quint32         _score;
    bool            _scoreChanged;
    bool            _livesChanged;
    bool            _shield;

public:
    //Constructeurs
    Ship(qint32 id, const QPointF &position, qint32 shipNumber);

    void            rotateShipLeft();
    void            rotateShipRight();
    void            addScore(quint32 score);
    bool            changeLife(qint32 change);
    void            grantShield();
    bool            removeShield();

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
    void            lives(quint32 lives);
    quint32         lives() const;
    bool            livesChanged();
    bool            haveShield();

    // Entity interface
public:
    bool            makeEntityMove() override;
    QPointF         center() const override;
};

#endif // SHIP_HH
