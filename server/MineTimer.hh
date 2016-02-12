#ifndef MINETIMER_HH
# define MINETIMER_HH

# include <QTimer>
# include <QObject>

class Mine;

class MineTimer : public QObject
{
    Q_OBJECT
private:
    Mine            &_mine;
    QTimer          _timer;

public:
    MineTimer(Mine &mine);

private slots:
    void            activate();
};

# include "Mine.hh"

#endif // MINETIMER_HH
