#ifndef ELEMENT_HH
# define ELEMENT_HH

# include <QPolygon>

# include "Minestorm.hh"

class Element
{
private:
    qint32          _imgId;
    QPolygon        _polygon;

public:
    Element(qint32 imgId, const QPolygon &polygon);
    Element();
    virtual ~Element();

    qint32          imgId() const;
    const QPolygon  &polygon() const;
};

#endif // ELEMENT_HH
