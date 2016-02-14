#ifndef FPSCOUNTER_HH
# define FPSCOUNTER_HH

# include <QTimer>
# include <QColor>
# include <QBrush>

# include "IDrawable.hh"
# include "Minestorm.hh"

class FpsCounter : public QObject
{
    Q_OBJECT

private:
    quint32         _frameCount;
    QString         _text;
    QColor          _color;
    QBrush          _brush;
    QPoint          _position;
    QTimer          _timer;

public:
    FpsCounter();

    void            start();
    void            stop();
    void            frameDraw();

    const QString   &fpsText() const;

    // IDrawable interface (Pb with QOBject..)
public:
    void            draw(QPainter &painter, Images &images) const;

signals:
    void            stopTimer();

private slots:
    void            count();
};

#endif // FPSCOUNTER_HH
