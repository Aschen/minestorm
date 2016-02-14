#ifndef PLAYER_HH
# define PLAYER_HH

# include "Ship.hh"

class Player
{
private:
    const qint32            _idClient;
    const quint32           _number;
    const QPoint            _spawn;
    QSharedPointer<Entity>  _ship;

public:
    explicit Player(qint32 idClient, quint32 number, const QPoint &spawn);
    ~Player();

    QSharedPointer<Entity>  startShooting();
    void                    stopShooting();

    QSharedPointer<Entity>  &entity();
    Ship                    &ship();
    quint32                 number() const;
    const QPoint            &spawn() const;
    bool                    available() const;
    qint32                  idClient() const;
    quint32                 score() const;
    quint32                 lives() const;
};

#endif // PLAYER_HH
