#include "MineTimer.hh"

MineTimer::MineTimer(Mine &mine)
    : _mine(mine)
{
    quint32     delay = rand() % MINE_MAX_DELAY;

    DEBUG("MineTimer::MineTime() : delay:" << delay, false);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(activate()));
    _timer.setSingleShot(true);
    _timer.start(delay * 1000);
}

void MineTimer::activate()
{
    _mine.activate();
}
