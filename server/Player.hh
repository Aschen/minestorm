#ifndef PLAYER_HH
# define PLAYER_HH

# include <QObject>
# include <QTimer>

# include "Ship.hh"

class Player : public QObject
{
    Q_OBJECT

private:
    const qint32            _idClient;
    const quint32           _number;
    const QPoint            _spawn;
    QSharedPointer<Entity>  _ship;
    bool                    _acceptShot;
    QTimer                  _shotTimer;
    EntityList              *_shots;

public:
    explicit Player(qint32 idClient, quint32 number, const QPoint &spawn);
    ~Player();

    void                    startShooting(EntityList *shots);
    void                    stopShooting();
    bool                    shot(QSharedPointer<Entity> &shot);

    QSharedPointer<Entity>  &entity();
    Ship                    &ship();
    quint32                 number() const;
    const QPoint            &spawn() const;
    bool                    available() const;
    qint32                  idClient() const;
    quint32                 score() const;
    quint32                 lives() const;

signals:
    void                    stopTimer();

private slots:
    void                    shoot();
};

#endif // PLAYER_HH
