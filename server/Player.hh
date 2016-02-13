#ifndef PLAYER_HH
# define PLAYER_HH

# include "Ship.hh"

class Player
{
private:
    const quint32           _number;
    const QPoint            _spawn;
    bool                    _available;
    qint32                  _idClient;
    QSharedPointer<Entity>  _ship;

public:
    explicit Player(quint32 number, const QPoint &spawn);

    QSharedPointer<Entity>  &newPlayer(qint32 idClient);
    void                    playerLeft();

    Ship                    &ship();
    quint32                 number() const;
    const QPoint            &spawn() const;
    bool                    available() const;
    qint32                  idClient() const;
    quint32                 score() const;
    quint32                 lives() const;
};

#endif // PLAYER_HH
