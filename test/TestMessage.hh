#ifndef TESTMESSAGE_HH
# define TESTMESSAGE_HH

# include <QtTest/QTest>

# include "MessageMouse.hh"
# include "MessageObjects.hh"

class TestMessage : public QObject
{
    Q_OBJECT

private slots:
    void        createMouseEvent();
    void        createKeyEvent();
    void        createInfoObjects();
};

#endif // TESTMESSAGE_HH
