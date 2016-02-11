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

private:
    qint32          _id;
    TypeMine        _type;
    QTime           _birthDate;
    int             _size;
    QColor          _color;
    Qt::BrushStyle _brushStyle;

public:
    //Constructor
    Mine(qint32 i, TypeMine type, QPointF point, QTime birthDate);

    //Methods
    void            createPolygon(QPointF point);
    QPointF         center() const override;
    bool            makeEntityMove() override;

    //Getter & Setter
    int             size() const;
    void            setSize(int size);

    QColor          color() const;
    void            setColor(QColor color);

    Qt::BrushStyle  brushStyle() const;
    void            setBrushStyle(const Qt::BrushStyle &brushStyle);

    QTime           birthDate() const;
    void            setBirthDate(const QTime &birthDate);

    TypeMine        type() const;
    void            setType(const TypeMine &type);
};

#endif // MINE_HH
