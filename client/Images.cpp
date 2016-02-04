#include "Images.hh"

Images::Images()
    : _images(5)
{
    loadImages();
}

QImage Images::getImage(Element::Type type, qreal angle)
{
    QTransform  t;

    return _images[type]->transformed(t.rotate(angle));
}

// alien_blaster.bmp  space_duelist.bmp  star_warp.bmp  void_viper.bmp
void Images::loadImages()
{
    _images[Element::MINE] = QSharedPointer<QImage>(new QImage("images/mine.png"));
    _images[Element::SHIP_1] = QSharedPointer<QImage>(new QImage("images/alien_blaster.png"));
    _images[Element::SHIP_2] = QSharedPointer<QImage>(new QImage("images/space_duelist.png"));
    _images[Element::SHIP_3] = QSharedPointer<QImage>(new QImage("images/star_warp.png"));
    _images[Element::SHIP_4] = QSharedPointer<QImage>(new QImage("images/void_viper.png"));
}

