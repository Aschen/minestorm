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
# include "MessageObjects.hh"
# include "MessageScore.hh"
# include "MessageMouse.hh"
# include "MessageKey.hh"
# include "MessageLives.hh"
# include "Client.hh"
# include "Images.hh"
# include "Element.hh"
# include "PlayersInfos.hh"

class Display : public QObject
{
    Q_OBJECT

private:
    bool                _isRunning;
    const QSize         _size;
    QSharedPointer<Client>              _client;
    QSharedPointer<QVector<Element>>    _elements;
    quint32             _fps;
    QList<quint32>      _fpsValues;
    QString             _fpsText;
    Images              _images;
    QPixmap             _image;
    qint32              _angle;
    QPointF             _origin;
    QTimer              _fpsTimer;
    PlayersInfos        _playersInfos;


public:
    Display(const QSize &size, QObject *parent = nullptr);

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
    const QVector<Element> &elements() const;
    QPixmap             getTransformedImage(QPixmap image, QPointF pos, QPointF anchor, qreal rot, QPointF &origin);

private:
    void                receiveObjects(const QSharedPointer<QVector<Element>> &elements);
    void                receiveScore(quint32 playerNumber, quint32 score);
    void                receiveLives(quint32 playerNumber, quint32 lives);

signals:
    void                changed();

private slots:
    void                messageDispatcher(qint32 socketFd, const QString &msg);
    void                fpsCount();
};

#endif // DISPLAY_HH
