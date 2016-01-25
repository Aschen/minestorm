#ifndef MINE_HH
#define MINE_HH

# include <QColor>
# include <QPoint>
# include <QBrush>
# include <iostream>

using namespace std;

class Mine
{
public:
    enum TypeMine {
        Small,
        Medium,
        Big
    };

    //Constructeur
    Mine(TypeMine type, QPoint point);

    //Getter & Setter
    int size() const;
    void setSize(int size);

    QColor color() const;
    void setColor(QColor color);

    QPoint point() const;
    void setPoint(const QPoint &point);

    Qt::BrushStyle brushStyle() const;
    void setBrushStyle(const Qt::BrushStyle &brushStyle);

private:
    TypeMine _type;
    QPoint _point;
    int _size;
    QColor _color;
    Qt::BrushStyle _brushStyle;
};

#endif // MINE_HH
