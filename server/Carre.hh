#ifndef CARRE_HH
# define CARRE_HH

# include "Entity.hh"

class Carre : public Entity
{
private:
    qint32      _color;

public:
    Carre(qint32 id);
    Carre(qint32 id, const QPoint &a, qint32 size, qint32 color);
    virtual ~Carre();

    qint32      color() const;


};

#endif // CARRE_HH
