#ifndef IMAGES_HH
# define IMAGES_HH

# include <QBitmap>
# include <QHash>
# include <QSharedPointer>

# include <Minestorm.hh>

class Images
{
private:
    enum Type
    {
        SHIP_1  = 1,
        SHIP_2  = 2,
        SHIP_3  = 3,
        SHIP_4  = 4,
        MINE    = 5
    };

private:
    QHash<qint32, QSharedPointer<QBitmap>>  _images;


public:
    Images();
};

#endif // IMAGES_HH
