#ifndef ELEMENT_HH
# define ELEMENT_HH

# include <QPolygon>
# include <QPainter>

# include "Minestorm.hh"

class Element
{
public:
    enum Type
    {
        MINE    = 0,
        SHIP_1  = 1,
        SHIP_2  = 2,
        SHIP_3  = 3,
        SHIP_4  = 4
    };

private:
    Type            _type;
    QPolygon        _polygon;
    qreal           _angle;

public:
    Element(Type type, const QPolygon &polygon, qreal angle);
    Element();
    ~Element();

    QPoint          center() const;

    Type            type() const;
    const QPolygon  &polygon() const;
    qreal           angle() const;
};

#endif // ELEMENT_HH
