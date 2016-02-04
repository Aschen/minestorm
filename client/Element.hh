#ifndef ELEMENT_HH
# define ELEMENT_HH

# include <QPolygon>

# include "Minestorm.hh"

class Element
{
private:
    qint32          _id;
    QPolygon        _polygon;

public:
    Element(qint32 id, const QPolygon &polygon);
    Element();
    virtual ~Element();

    qint32          id() const;
    const QPolygon  &polygon() const;
};

#endif // ELEMENT_HH
