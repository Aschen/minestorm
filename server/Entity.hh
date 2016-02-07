#ifndef ENTITY_HH
# define ENTITY_HH

# define PI M_PI

# include <QPoint>
# include <QPolygonF>
# include <QVector>
# include <QList>
# include <QHash>
# include <QSharedPointer>
# include <QTransform>

# include <sstream>
# include <cmath>

# include "Minestorm.hh"

using namespace std;

class Entity : public QPolygonF
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
    qreal                   _speed;
    qint32                  _angle;
    Etat                    _etat;


public:
    Entity(qint32 id, Type type);
    virtual ~Entity();

    void                    addPoint(const QPointF &point);
    virtual QPointF          center() const = 0;

    bool                    isMoving();
    void                    incrementSpeed();
    void                    decrementSpeed();
    void                    rotate(qint32 angle);
    virtual bool            makeEntityMove();
    double                  getRadian(qint32 angle);
    void                    setEtatDead();


    Type                    type() const;
    qint32                  id() const;
    const QSize             &size() const; // rename it
    void                    size(const QSize &value); // rename it
    qreal                   speed() const;
    void                    speed(qreal value);
    qint32                  angle() const;
    void                    angle(qint32 value);
    Etat                    etat() const;
    void                    setEtat(const Etat &etat);
};

using EntityList = QList<QSharedPointer<Entity>>;
using EntityHash = QHash<qint32, QSharedPointer<Entity>>;

#endif // ENTITY_HH
