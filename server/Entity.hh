#ifndef ENTITY_HH
# define ENTITY_HH

# define PI M_PI

# include <QPoint>
# include <QPolygon>
# include <QVector>
# include <QList>
# include <QHash>
# include <QSharedPointer>
# include <QTransform>

# include <sstream>
# include <cmath>
# include "Minestorm.hh"
using namespace std;

class Entity : public QPolygon
{
public:
    enum Type
    {
        MINE = 0,
        SHIP = 1,
        SHOT = 2
    };
    enum Etat
    {
        DEAD = 0,
        ALIVE = 1
    };

protected:
    const Type              _type;
    const qint32            _id;
    QSize                   _size;
    qint32                  _speed;
    double                  _angle;
    Etat                    _etat;


public:
    Entity(qint32 id, Type type);
    virtual ~Entity();

    void                    addPoint(const QPoint &point);
    virtual QPoint          center() const = 0;

    bool                    isMoving();
    void                    incrementSpeed();
    void                    decrementSpeed();
    void                    rotate(qint32 angle);
    virtual bool            makeEntityMove();
    double                  getRadian(qint32 angle);


    Type                    type() const;
    qint32                  id() const;
    const QSize             &size() const; // rename it
    void                    size(const QSize &value); // rename it
    qint32                  speed() const;
    void                    speed(qint32 value);
    double                  angle() const;
    void                    angle(double value);
};

using EntityList = QList<QSharedPointer<Entity>>;
using EntityHash = QHash<qint32, QSharedPointer<Entity>>;

#endif // ENTITY_HH
