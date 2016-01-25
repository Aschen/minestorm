#ifndef DRAWABLEOBJECT_HH
# define DRAWABLEOBJECT_HH

# include <QPolygon>

# include <string>
# include <list>
# include <unordered_map>
# include <memory>

class DrawableObject : public QPolygon
{
private:
    const std::string   _name;

public:
    DrawableObject(const std::string &name);
    ~DrawableObject();

    const std::string   &name() const;
};

using DrawableObjectList = std::list<std::shared_ptr<DrawableObject>>;
using DrawableObjectMap = std::unordered_map<std::string, std::shared_ptr<DrawableObject>>;

#endif // DRAWABLEOBJECT_HH
