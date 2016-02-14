#include "Images.hh"

Images::Images()
    : _images(14)
{
    loadImages();
}

QImage Images::getImage(Element::Type type, qreal angle)
{
    if (angle != 0)
    {
        QMatrix     m;
        DEBUG("Images::getImages() : angle:" << angle, false);
        return _images[type]->transformed(m.rotate(angle));
    }
    else
    {
        DEBUG("Images::getImages() :" << angle, false);
        return *(_images[type].data());
    }
}

// alien_blaster.bmp  space_duelist.bmp  star_warp.bmp  void_viper.bmp
void Images::loadImages()
{
    _images[Element::MINE_S]     = QSharedPointer<QImage>(new QImage("images/mine_small.png"));
    _images[Element::MINE_M]     = QSharedPointer<QImage>(new QImage("images/mine_medium.png"));
    _images[Element::MINE_L]     = QSharedPointer<QImage>(new QImage("images/mine_large.png"));
    _images[Element::MINE_S_ON]  = QSharedPointer<QImage>(new QImage("images/mine_small_on.png"));
    _images[Element::MINE_M_ON]  = QSharedPointer<QImage>(new QImage("images/mine_medium_on.png"));
    _images[Element::MINE_L_ON]  = QSharedPointer<QImage>(new QImage("images/mine_large_on.png"));
    _images[Element::SHIP_1]     = QSharedPointer<QImage>(new QImage("images/alien_blaster.png"));
    _images[Element::SHIP_2]     = QSharedPointer<QImage>(new QImage("images/space_duelist.png"));
    _images[Element::SHIP_3]     = QSharedPointer<QImage>(new QImage("images/star_warp.png"));
    _images[Element::SHIP_4]     = QSharedPointer<QImage>(new QImage("images/void_viper.png"));
    _images[Element::SHIELD]     = QSharedPointer<QImage>(new QImage("images/shield.png"));
    _images[Element::SHOT]       = QSharedPointer<QImage>(new QImage("images/shot.png"));
    _images[Element::MINE_EXPLO] = QSharedPointer<QImage>(new QImage("images/explosion.png"));
    _images[Element::LIVE]       = QSharedPointer<QImage>(new QImage("images/live.png"));
}

