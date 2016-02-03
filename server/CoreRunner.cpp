#include "CoreRunner.hh"

CoreRunner::CoreRunner(qint32 cps)
    : _core(QSharedPointer<Core>(new Core(cps)))
{
    DEBUG("CoreRunner::CoreRunner()", true);
}

CoreRunner::~CoreRunner()
{
    DEBUG("CoreRunner::~CoreRunner()", true);
}

void CoreRunner::stop()
{
    DEBUG("CoreRunner::stop()", true);

    exit(0);
}

void CoreRunner::run()
{
    DEBUG("CoreRunner::run()", true);

    _core->startGame();
    exec();
}

