#ifndef CARRE_HH
# define CARRE_HH

# include "Entity.hh"

class Carre : public Entity
{
public:
    Carre(string name);
    Carre(string name, const QPoint &a, int size);
    virtual ~Carre();
};

#endif // CARRE_HH
