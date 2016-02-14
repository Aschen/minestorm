#include "Element.hh"


Element::Element(Type type, const QPolygon &polygon, qreal angle, bool shield, const QPoint &center)
    : _type(type),
      _polygon(polygon),
      _angle(angle),
      _center(center),
      _imageCenter(_center.x() - 16, _center.y() - 16),
      _shield(shield)
{
}
Element::Element(Type type, const QPolygon &polygon, bool sound)
    : _type(type),
      _polygon(polygon),
      _angle(0.0),
      _playSound(sound)

{
}

Element::Element(Element::Type type, const QPolygon &polygon, const QPoint &center)
    : _type(type),
      _polygon(polygon),
      _center(center)
{
}

Element::Element()
{
}

Element::~Element()
{
}

void Element::draw(QPainter &painter, Images &images) const
{
    switch (_type)
    {
    case Element::MINE_S:
    case Element::MINE_L:
    case Element::MINE_M:
    case Element::MINE_S_ON:
    case Element::MINE_L_ON:
    case Element::MINE_M_ON:
        painter.drawImage(_center, images.getImage(_type));
        break;
    case Element::SHIP_1:
    case Element::SHIP_2:
    case Element::SHIP_3:
    case Element::SHIP_4:

        /* Draw shield */
        if (shielded())
        {
            DEBUG("Element::draw() Shield", false);
            painter.drawImage(QRect(QPoint(_center.x() - 20, _center.y() - 20),QSize(40,40)),
                              images.getImage(Element::SHIELD, _angle));
//            painter.setBrush(QBrush("#98F5FF"));
//            painter.setPen(QColor("#98F5FF"));
//            painter.drawEllipse(_center, SHIP_SIZE / 2, SHIP_SIZE / 2);
        }

        painter.setPen(QColor("#AAAAAA"));
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawConvexPolygon(_polygon);
        painter.drawImage(QRect(QPoint(_imageCenter .x(), _imageCenter.y()),QSize(32,32))
                        , images.getImage(_type, _angle));
        break;

    case Element::SHOT:
        if(playSound())
        {
            DEBUG("Projectile:playsound" << playSound(), false);
            QSound::play("sound/shot.wav");
        }
        painter.setPen(QColor(255, 0, 51)); // RED
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawConvexPolygon(_polygon);
        painter.drawImage(QRect(QPoint(_center.x() - 10, _center.y() - 10), QSize(20, 20)),
                          images.getImage(_type, _angle));

        break;
    }
}

Element::Type Element::type() const
{
    return _type;
}

const QPolygon &Element::polygon() const
{
    return _polygon;
}

qreal Element::angle() const
{
    return _angle;
}

bool Element::shielded() const
{
    return _shield;
}

void Element::playSound(bool value)
{
    _playSound = value;
}

bool Element::playSound() const
{
    return _playSound;
}

const QPoint &Element::center() const
{
    return _center;
}

const QPoint &Element::imageCenter() const
{
    return _imageCenter;
}
