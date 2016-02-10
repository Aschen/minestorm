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

public:
    //Constructeurs
    Ship(qint32 id, const QPointF &position, qint32 shipNumber);

    void            rotateShipLeft();
    void            rotateShipRight();
    bool            changeLife(qint32 change);

    //Getter & Setter
    quint32         vie() const;
    void            setVie(quint32 vie);
    QRect           rect() const;
    void            setRect(const QRect &rect);
    quint32         shipNumber() const;
    void            shipNumber(quint32 shipNumber);
    bool            makeEntityMove() override;

    // Entity interface
public:
    QPointF          center() const override;
};

#endif // SHIP_HH
