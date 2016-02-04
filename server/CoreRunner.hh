#ifndef CORERUNNER_HH
# define CORERUNNER_HH

# include <QThread>

# include "Core.hh"

class CoreRunner : public QThread
{
    Q_OBJECT

private:
    QSharedPointer<Core>    _core;

public:
    CoreRunner();
    ~CoreRunner();

public slots:
    void                    stop();

protected:
    void                    run() Q_DECL_OVERRIDE;
};

#endif // CORERUNNER_HH
