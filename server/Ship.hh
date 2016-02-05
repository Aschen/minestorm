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
    QRect           _rect;
    QImage          _img;

public:
    //Constructeurs
    Ship(qint32 id, QPoint position);

    void            createShipPolygon();
    void            rotateShipLeft();
    void            rotateShipRight();

    //Getter & Setter
    quint32         vie() const;
    void            setVie(quint32 vie);
    QRect           rect() const;
    void            setRect(const QRect &rect);

    QImage          img() const;
    void            setImage(const QImage &img);
};

#endif // SHIP_HH
