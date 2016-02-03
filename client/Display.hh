#ifndef DISPLAY_HH
# define DISPLAY_HH

# include <QObject>
# include <QTimer>
# include <QSize>
# include <QMutex>
# include <QPainter>
# include <QBrush>
# include <QVector>
# include <QPolygon>
# include <QApplication>

# include "Minestorm.hh"
# include "MessageFactory.hpp"
# include "Client.hh"
# include "Element.hh"

class Display : public QObject
{
    Q_OBJECT

private:
    QTimer              _timer;
    bool                _isRunning;
    const QSize         _size;
    const qint32        _fps;
    QSharedPointer<Client>              _client;
    QSharedPointer<QVector<Element>>    _objects;
    QMutex              _objectsMutex;

public:
    Display(const QSize &size, qint32 fps = 25, QObject *parent = nullptr);

    void                draw(QPainter &painter, QRect &size);
    void                startDisplay();

    // Events triggered from Gameboard
    void                mousePressed(qint32 x, qint32 y);
    void                mouseReleased(qint32 x, qint32 y);
    void                keyPressed(qint32 key);
    void                keyReleased(qint32 key);

    // Events triggered from Controller
    void                startNewGame();
    void                joinGame(const QString &host);
    void                exitGame();


    const QSize         &size() const;
    bool                isRunning() const;
    const QVector<Element> &objects() const;


signals:
    void                changed();

public slots:
    void                receiveObjects(const QSharedPointer<QVector<Element> > &objects);

private slots:
    void                update();
    void                messageDispatcher(qint32 socketFd, const QString &msg);
};

#endif // DISPLAY_HH
