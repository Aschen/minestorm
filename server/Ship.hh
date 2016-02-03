#ifndef SHIP_HH
# define SHIP_HH

# include <QRect>
# include "QImage"

#include "Entity.hh"

class Ship : public Entity
{
public:
    //Constructeurs
    Ship(qint32 name);
    Ship(qint32 name, QRect rect, int vie);

    void            drawShip();

    //Getter & Setter
    int             vie() const;
    void            setVie(int vie);
    QRect           rect() const;
    void            setRect(const QRect &rect);

    QImage          img() const;
    void            setImage(const QImage &img);

private:
    int             _vie;
    QRect           _rect;
    QImage          _img;

};

#endif // SHIP_HH
