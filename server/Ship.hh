#ifndef SHIP_HH
# define SHIP_HH

# include <QRect>
# include "QImage"

class Ship
{
public:
    //Constructeurs
    Ship();
    Ship(QRect rect, int vie);

    //Getter & Setter
    int vie() const;
    void setVie(int vie);
    QRect rect() const;
    void setRect(const QRect &rect);

    QImage img() const;
    void setImg(const QImage &img);

private:
    int _vie;
    QRect _rect;
    QImage _img;
};

#endif // SHIP_HH
