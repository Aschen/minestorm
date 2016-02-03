#include "TestMessage.hh"

void TestMessage::createMouseEvent()
{
    MessageMouse         mPressed("1 21 42");
    MessageMouse         mReleased("2 -21 -42");

    QVERIFY(mPressed.type() == MessageBase::MOUSE_PRESSED);
    QVERIFY(mReleased.type() == MessageBase::MOUSE_RELEASED);

    QVERIFY(mPressed.x() == 21);
    QVERIFY(mPressed.y() == 42);

    QVERIFY(mReleased.x() == -21);
    QVERIFY(mReleased.y() == -42);
}

void TestMessage::createKeyEvent()
{
//    Message         kPressed("3 21");
//    Message         kReleased("4 42");

//    QVERIFY(kPressed.type() == Message::KEY_PRESSED);
//    QVERIFY(kReleased.type() == Message::KEY_RELEASED);

//    QVERIFY(kPressed.objects() == nullptr);
//    QVERIFY(kPressed.point() == nullptr);
//    QVERIFY(kPressed.keyCode() == 21);

//    QVERIFY(kReleased.keyCode() == 42);
}

void TestMessage::createInfoObjects()
{
    MessageObjects         fromMessage("7 3  2 42 21 84 48  3 12 21 34 43 56 65  1 23 22");

    QVERIFY(fromMessage.type() == MessageBase::INFO_OBJECTS);

    QVERIFY(fromMessage.objects()->size() == 3);
    QVERIFY(fromMessage.objects()->at(0).size() == 2);
    QVERIFY(fromMessage.objects()->at(0).at(0).x() == 42);
    QVERIFY(fromMessage.objects()->at(0).at(0).y() == 21);
    QVERIFY(fromMessage.objects()->at(1).size() == 3);
    QVERIFY(fromMessage.objects()->at(1).at(0).y() == 21);
    QVERIFY(fromMessage.objects()->at(1).at(2).x() == 56);
    QVERIFY(fromMessage.objects()->at(2).size() == 1);
    QVERIFY(fromMessage.objects()->at(2).at(0).x() == 23);
    QVERIFY(fromMessage.objects()->at(2).at(0).y() == 22);

    MessageObjects      fromObjects(*(fromMessage.objects()));

    QVERIFY(fromObjects.messageString() == "7 3 2 42 21 84 48 3 12 21 34 43 56 65 1 23 22 ");
}
