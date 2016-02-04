#ifndef IMAGES_HH
# define IMAGES_HH

# include <QBitmap>
# include <QImage>
# include <QHash>
# include <QVector>
# include <QSharedPointer>
# include <QTransform>

# include "Minestorm.hh"
# include "Element.hh"
# include "Entity.hh"

class Images
{
private:

private:
    QVector<QSharedPointer<QImage>>    _images;

public:
    Images();

    QImage getImage(Element::Type type, qreal angle);

private:
    void                loadImages();

};

#endif // IMAGES_HH
