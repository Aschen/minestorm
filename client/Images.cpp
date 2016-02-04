#include "Images.hh"

Images::Images()
{
    loadImages();
}

// alien_blaster.bmp  space_duelist.bmp  star_warp.bmp  void_viper.bmp
void Images::loadImages()
{
    _images[MINE] = QSharedPointer<QBitmap>(new QBitmap("images/mine.bmp"));
    _images[SHIP_1] = QSharedPointer<QBitmap>(new QBitmap("images/alien_blaster.bmp"));
    _images[SHIP_2] = QSharedPointer<QBitmap>(new QBitmap("images/space_duelist.bmp"));
    _images[SHIP_3] = QSharedPointer<QBitmap>(new QBitmap("images/star_warp.bmp"));
    _images[SHIP_4] = QSharedPointer<QBitmap>(new QBitmap("images/void_viper.bmp"));


}

