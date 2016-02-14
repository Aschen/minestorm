#ifndef IDRAWABLE_HH
# define IDRAWABLE_HH

# include <QPainter>

class Images;

class IDrawable
{
public:
    virtual void        draw(QPainter &painter, Images &images) const = 0;
};

#endif // IDRAWABLE_HH
