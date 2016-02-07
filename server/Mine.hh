#ifndef MINE_HH
#define MINE_HH

# include <QColor>
# include <QPoint>
# include <QBrush>
# include <QTime>
# include <iostream>

# include "Entity.hh"

using namespace std;

class Mine : public Entity
{
public:
    enum TypeMine {
        Small = 0,
        Medium = 5,
        Big = 6
    };

    //Constructeur
    Mine(qint32 i, TypeMine type, QPoint point, QTime birthDate);

    //Getter & Setter
    int size() const;
    void setSize(int size);

    QColor color() const;
    void setColor(QColor color);

    Qt::BrushStyle brushStyle() const;
    void setBrushStyle(const Qt::BrushStyle &brushStyle);

    QTime birthDate() const;
    void setBirthDate(const QTime &birthDate);

    TypeMine type() const;
    void setType(const TypeMine &type);

private:
    TypeMine        _type;
    QTime           _birthDate;
    int             _size;
    QColor          _color;
    Qt::BrushStyle _brushStyle;

public:
    QPoint center() const override;
};

#endif // MINE_HH
