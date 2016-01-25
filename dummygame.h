#ifndef DUMMYGAME_H
#define DUMMYGAME_H
#include "game.h"

#include <QPoint>
#include <QBrush>
#include <vector>
using namespace std;
/**
 * @brief La classe DummyGame donne un exemple de l'utilisation de la classe Game
 */
class DummyGame : public Game
{
    Q_OBJECT
public:
    DummyGame(const QSize &size,QObject *parent = nullptr);
    virtual void draw(QPainter &painter, QRect &rect) override;
    void mousePressed( int x, int y) override;
    void keyPressed( int key ) override;
    void keyReleased( int key ) override;
    void mouseReleased( int x, int y) override;
    void mouseMoved(int x, int y) override;
private:
    virtual void step();
    void initialize();
    void addEllipse( int x, int y, Qt::BrushStyle style = Qt::SolidPattern);

    vector<QPoint> _points;
    vector<int> _pointsSize;
    vector<QColor> _pointsColor;
    vector<Qt::BrushStyle> _pointsPattern;
    Qt::BrushStyle _currentStyle;
};

#endif // DUMMYGAME_H
