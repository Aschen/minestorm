#ifndef IMAGES_HH
# define IMAGES_HH

# include <QBitmap>
# include <QHash>
# include <QVector>
# include <QSharedPointer>

# include "Minestorm.hh"
# include "Element.hh"
# include "Entity.hh"

class Images
{
private:
    enum Type
    {
        MINE    = 0,
        SHIP_1  = 1,
        SHIP_2  = 2,
        SHIP_3  = 3,
        SHIP_4  = 4
    };

private:
    QVector<QSharedPointer<QBitmap>>    _images;

public:
    Images();

private:
    void            loadImages();

};

#endif // IMAGES_HH
