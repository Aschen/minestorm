#ifndef SHIP_HH
# define SHIP_HH

# define PI 3.141592654

# include <QRect>
# include "QImage"
# include "Entity.hh"
# include "Minestorm.hh"

class Ship : public Entity
{
private:
    quint32         _vie;
    quint32         _shipNumber;

public:
    //Constructeurs
    Ship(qint32 id, const QPoint &position, qint32 shipNumber);

    void            createShipPolygon();
    void            moveShipForward();
    void            rotateShipLeft();
    void            rotateShipRight();
    double          getRadian();

    //Getter & Setter
    quint32         vie() const;
    void            setVie(quint32 vie);
    QRect           rect() const;
    void            setRect(const QRect &rect);
    quint32         shipNumber() const;
    void            shipNumber(quint32 shipNumber);

    // Entity interface
public:
    QPoint          center() const override;
};

#endif // SHIP_HH
