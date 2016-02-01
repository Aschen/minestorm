#ifndef TESTMESSAGE_HH
# define TESTMESSAGE_HH

# include <QtTest/QTest>

# include "Message.hh"

class TestMessage : public QObject
{
    Q_OBJECT

private slots:
    void        createMouseEvent();
    void        createKeyEvent();
    void        createInfoObjects();
};

#endif // TESTMESSAGE_HH
