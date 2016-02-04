#ifndef ELEMENT_HH
# define ELEMENT_HH

# include <QPolygon>

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

public:
    Element(Type type, const QPolygon &polygon);
    Element();
    virtual ~Element();

    Type            type() const;
    const QPolygon  &polygon() const;
};

#endif // ELEMENT_HH
