#include <test/TestMessage.hh>


void        runTests()
{
    TestMessage     message;

    QTest::qExec(&message);
}
