#include "dummygame.h"

#include <QPainter>
#include <QRect>
#include <QColor>

#include <iostream>

DummyGame::DummyGame(const QSize &size,QObject *parent):Game(size,parent), _currentStyle(Qt::SolidPattern) {
}

void DummyGame::addEllipse( int x, int y, Qt::BrushStyle style) {
    _points.push_back(QPoint(x,y));
    _pointsSize.push_back(rand()%50);
    _pointsColor.push_back(QColor(rand()%255,rand()%255,rand()%255));
    _pointsPattern.push_back(style);
}

void DummyGame::step() {    
    auto x = rand() %size().width();
    auto y = rand() %size().height();
    addEllipse( x, y );
}
void DummyGame::draw(QPainter &painter, QRect &rect) {
    painter.fillRect(rect, QColor(0,0,0));
    for(auto i=0u;i < _points.size();++i) {
        painter.setPen(_pointsColor[i]);
        QBrush brush(_pointsColor[i],_pointsPattern[i]);
        painter.setBrush(brush);
        auto x_ratio = (double)rect.width() / size().width();
        auto y_ratio = (double)rect.height() / size().height();
        auto x = _points[i].x() * x_ratio;
        auto y = _points[i].y() * y_ratio;
        painter.drawEllipse(x,y,_pointsSize[i]*x_ratio,_pointsSize[i]*y_ratio);
    }

}
void DummyGame::initialize() {
    _points.clear();
    _pointsSize.clear();
    _pointsColor.clear();
    _pointsPattern.clear();
    _currentStyle = Qt::SolidPattern;
}
void DummyGame::mousePressed( int x, int y) {
    addEllipse(x,y,_currentStyle);
    emit changed();
}
void DummyGame::keyPressed( int key ) {
    switch(key) {
    case Qt::Key_1: _currentStyle = Qt::SolidPattern;
        break;
    case Qt::Key_2: _currentStyle = Qt::CrossPattern;
        break;
    case Qt::Key_3: _currentStyle = Qt::VerPattern;
        break;
    case Qt::Key_4: _currentStyle = Qt::HorPattern;
        break;
    }
}
void DummyGame::keyReleased( int /* key */) {
}
void DummyGame::mouseReleased( int /* x */, int /* y */) {
}

void DummyGame::mouseMoved(int /* x */, int /* y */) {

}

