#ifndef ENTITY_HH
# define ENTITY_HH

# include <QPoint>
# include <QPolygon>
# include <QVector>
# include <QList>
# include <QHash>
# include <QSharedPointer>

# include <sstream>

# include "Minestorm.hh"
using namespace std;

class Entity : public QPolygon
{
public:
    static const char * const           TYPE_DISPLAY[];
    enum Type
    {
        MINE = 0,
        SHIP = 1,
        SHOT = 2,
        CARRE= 9 // Pour test
    };

protected:
    const Type              _type;
    const qint32            _id;
    QPoint                  _xy;
    QSize                   _size;
    qint32                  _speed;
    double                  _angle;


public:
    Entity(qint32 id, Type type);
    virtual ~Entity();

    void                    addPoint(const QPoint &point);

    Type                    type() const;
    qint32                  id() const;
    const QPoint            &xy() const;
    void                    xy(const QPoint &value);
    qint32                  x() const;
    qint32                  y() const;
    const QSize             &size() const;
    void                    size(const QSize &value);
    qint32                  speed() const;
    void                    speed(qint32 value);
    double                  angle() const;
    void                    angle(double value);

    const string            dump() const;
};

using EntityList = QList<QSharedPointer<Entity>>;
using EntityHash = QHash<qint32, QSharedPointer<Entity>>;

#endif // ENTITY_HH
