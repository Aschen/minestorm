#include "CoreRunner.hh"

CoreRunner::CoreRunner()
    : _core(QSharedPointer<Core>(new Core(CYCLE_PER_S)))
{
    DEBUG("CoreRunner::CoreRunner()", false);
}

CoreRunner::~CoreRunner()
{
    DEBUG("CoreRunner::~CoreRunner()", false);
}

void CoreRunner::stop()
{
    DEBUG("CoreRunner::stop()", false);

    exit(0);
}

void CoreRunner::run()
{
    DEBUG("CoreRunner::run()", false);

    _core->startGame();
    exec();
}

