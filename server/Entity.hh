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
        SHOT = 2,
        ALL  = 3
    };
    enum Etat
    {
        DEAD = 0,
        ALIVE = 1,
        INVINCIBLE
    };

protected:
    Type                    _type;
    QSize                   _size;
    qreal                   _speed;
    qint32                  _angle;
    Etat                    _etat;
    qreal                   _vx;
    qreal                   _vy;



public:
    Entity(Type type);
    virtual ~Entity();

    void                    addPoint(const QPointF &point);
    void                    addPoint(const qreal x, const qreal y);
    virtual QPointF         center() const = 0;

    bool                    isMoving();
    void                    incrementSpeed();
    void                    decrementSpeed(qint32 value);
    void                    rotate(qint32 angle);
    virtual bool            makeEntityMove();
    double                  getRadian(qint32 angle);
    virtual void            setEtatDead();
    bool                    isDead();

    Type                    type() const;
    void                    type(Entity::Type type);
    const QSize             &size() const; // rename it
    void                    size(const QSize &value); // rename it
    qreal                   speed() const;
    void                    speed(qreal value);
    qint32                  angle() const;
    void                    angle(qint32 value);
    Etat                    etat() const;
    void                    setEtat(const Etat &etat);
    qreal                   vy() const;
    void                    vy(qreal value);
    qreal                   vx() const;
    void                    vx(qreal value);
};

using EntityList = QList<QSharedPointer<Entity>>;
using EntitiesHash = QHash<Entity::Type, EntityList>;

using EntityVector = QVector<QSharedPointer<Entity>>;

#endif // ENTITY_HH
