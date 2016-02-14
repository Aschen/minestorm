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
# include "MessagePlayersInfos.hh"
# include "MessagePseudo.hh"
# include "MessageMouse.hh"
# include "MessageKey.hh"
# include "Client.hh"
# include "Images.hh"
# include "Element.hh"
# include "PlayersInfos.hh"
# include "FpsCounter.hh"

class Display : public QObject
{
    Q_OBJECT

private:
    bool                _isRunning;
    const QSize         _size;
    QSharedPointer<Client>              _client;
    QSharedPointer<QVector<Element>>    _elements;
    Images              _images;
    PlayersInfos        _playersInfos;
    FpsCounter          _fpsCounter;


public:
    Display(const QSize &size, QObject *parent = nullptr);

    void                draw(QPainter &painter, QRect &size);
    void                startDisplay();
    void                stopDisplay();

    // Events triggered from Gameboard
    void                mousePressed(qint32 x, qint32 y);
    void                mouseReleased(qint32 x, qint32 y);
    void                keyPressed(qint32 key);
    void                keyReleased(qint32 key);

    // Events triggered from Controller
    void                startNewGame();
    void                joinGame(const QString &host, const QString &pseudo);
    void                exitGame();

    // Key events for Display only
    void                stopGame();

    const QSize         &size() const;
    bool                isRunning() const;
    const QVector<Element> &elements() const;

private:
    void                receiveObjects(const QSharedPointer<QVector<Element>> &elements);

signals:
    void                changed();

private slots:
    void                messageDispatcher(qint32 socketFd, const QString &msg);
};

#endif // DISPLAY_HH
