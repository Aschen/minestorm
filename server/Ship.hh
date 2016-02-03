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
    QRect           _rect;
    qint32          _shipId;
    QImage          _img;

public:
    //Constructeurs
    Ship(qint32 id);
    Ship(qint32 id, QRect rect, quint32 vie, qint32 shipId);

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

    QImage          img() const;
    void            setImage(const QImage &img);
    qint32          shipId() const;
};

#endif // SHIP_HH
