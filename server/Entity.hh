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

class Entity : public QPolygon
{
public:
    static const char * const           TYPE_DISPLAY[];
    enum Type
    {
        MINE = 0,
        SHIP = 1,
        SHOT = 2,
        CARRE= 3 // Pour test
    };

protected:
    const Type              _type;
    const string            _name;
    int                     _speed;

public:
    Entity(string name, Type type);
    virtual ~Entity();

    void                    addPoint(const QPoint &point);

    Type                    type() const;
    const string            name() const;
    int                     speed() const;
    void                    speed(int value);

    const string            dump() const;
};

using EntityList = QList<std::shared_ptr<Entity>>;
using EntityHash = QHash<std::string, std::shared_ptr<Entity>>;

#endif // ENTITY_HH
