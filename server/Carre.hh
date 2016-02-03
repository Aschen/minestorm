#ifndef CARRE_HH
# define CARRE_HH

# include "Entity.hh"

class Carre : public Entity
{
public:
    Carre(qint32 id);
    Carre(qint32 id, const QPoint &a, qint32 size);
    virtual ~Carre();
};

#endif // CARRE_HH
