#ifndef CORE_HH
# define CORE_HH

# include <QPainter>
# include <QBrush>
# include <QPolygon>
# include <memory>
# include <list>
# include "DrawableObject.hh"
# include "game.h"

using namespace std;

class Core : public Game
{
private:
    list<shared_ptr<DrawableObject>>         _objects;

public:
    Core(const QSize &size, QObject *parent = nullptr);



    // Game interface
public:
    void draw(QPainter &painter, QRect &size) override;
    void mousePressed(int x, int y) override;
    void mouseReleased(int x, int y) override;
    void mouseMoved(int x, int y) override;
    void keyPressed(int key) override;
    void keyReleased(int key) override;

protected:
    void step() override;
    void initialize() override;
};

#endif // CORE_HH
