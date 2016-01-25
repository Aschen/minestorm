#ifndef DISPLAY_HH
# define DISPLAY_HH

# include <QObject>
# include <QTimer>
# include <QSize>

# include "Minestorm.hh"

class QPainter;
class QRect;

class Display : public QObject
{
    Q_OBJECT

private:
    QTimer          _timer;
    bool            _isRunning;
    QSize           _size;

public:
    Display(const QSize &size, QObject *parent = nullptr);

    void            draw(QPainter &painter, QRect &size);

    void            mousePressed(int x, int y);
    void            mouseReleased(int x, int y);
    void            mouseMoved(int x, int y);
    void            keyPressed(int key);
    void            keyReleased(int key);

    void            start();
    void            pause();
    void            reset();

    const QSize     &size() const;
    bool            isRunning() const;


protected:
    void            initialize();


signals:
    void            changed();

private slots:
    void            update();
};

#endif // DISPLAY_HH
