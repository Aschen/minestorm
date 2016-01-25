#ifndef ENTITY_HH
# define ENTITY_HH

# include <QPoint>
# include <QPolygon>
# include <QVector>
# include <QList>
# include <QHash>

# include <sstream>
# include <memory>

using namespace std;

class Entity
{
public:
    static const char * const           TYPE_DISPLAY[];
    enum Type
    {
        MINE = 0,
        SHIP = 1,
        SHOT = 2
    };

private:
    const Type              _type;
    const string            _name;
    int                     _speed;
    QVector<QPoint>         _points;

public:
    Entity(string name, Type type);
    virtual ~Entity();

    void                    addPoint(const QPoint &point);

    Type                    type() const;
    const string            name() const;
    const QVector<QPoint>   points() const;
    int                     speed() const;
    void                    speed(int value);

    const string            dump() const;
};

Entity                  &operator<<(Entity &entity, const QPoint &point);

using EntityList = QList<std::shared_ptr<Entity>>;
using EntityHash = QHash<std::string, std::shared_ptr<Entity>>;

#endif // ENTITY_HH
