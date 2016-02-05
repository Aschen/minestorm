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
        MINE_S  = 0,
        SHIP_1  = 1,
        SHIP_2  = 2,
        SHIP_3  = 3,
        SHIP_4  = 4,
        MINE_M  = 5,
        MINE_L  = 6,
        SHOT    = 7
    };

private:
    Type            _type;
    QPolygon        _polygon;
    qreal           _angle;
    QPoint          _center;
    QPoint          _imageCenter;

public:
    Element(Type type, const QPolygon &polygon, qreal angle, const QPoint &center);
    Element(Type type, const QPolygon &polygon);
    Element();
    ~Element();

    const QPoint    &center() const;
    const QPoint    &imageCenter() const;

    Type            type() const;
    const QPolygon  &polygon() const;
    qreal           angle() const;
};

#endif // ELEMENT_HH
