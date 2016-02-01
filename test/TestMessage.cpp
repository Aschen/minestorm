#include "TestMessage.hh"

void TestMessage::createMouseEvent()
{
    Message         mPressed("1 21 42");
    Message         mReleased("2 -21 -42");

    QVERIFY(mPressed.type() == Message::MOUSE_PRESSED);
    QVERIFY(mReleased.type() == Message::MOUSE_RELEASED);

    QVERIFY(mPressed.keyCode() == -1);
    QVERIFY(mPressed.objects() == nullptr);
    QVERIFY(mPressed.point()->x() == 21);
    QVERIFY(mPressed.point()->y() == 42);

    QVERIFY(mReleased.point()->x() == -21);
    QVERIFY(mReleased.point()->y() == -42);
}

void TestMessage::createKeyEvent()
{
    Message         kPressed("3 21");
    Message         kReleased("4 42");

    QVERIFY(kPressed.type() == Message::KEY_PRESSED);
    QVERIFY(kReleased.type() == Message::KEY_RELEASED);

    QVERIFY(kPressed.objects() == nullptr);
    QVERIFY(kPressed.point() == nullptr);
    QVERIFY(kPressed.keyCode() == 21);

    QVERIFY(kReleased.keyCode() == 42);
}

void TestMessage::createInfoObjects()
{
    Message         objects("7 3  2 42 21 84 48  3 12 21 34 43 56 65  1 23 22");

    QVERIFY(objects.type() == Message::INFO_OBJECTS);

    QVERIFY(objects.point() == nullptr);
    QVERIFY(objects.keyCode() == -1);
    QVERIFY(objects.objects()->size() == 3);
    QVERIFY(objects.objects()->at(0).size() == 2);
    QVERIFY(objects.objects()->at(0).at(0).x() == 42);
    QVERIFY(objects.objects()->at(0).at(0).y() == 21);
    QVERIFY(objects.objects()->at(1).size() == 3);
    QVERIFY(objects.objects()->at(1).at(0).y() == 21);
    QVERIFY(objects.objects()->at(1).at(2).x() == 56);
    QVERIFY(objects.objects()->at(2).size() == 1);
    QVERIFY(objects.objects()->at(2).at(0).x() == 23);
    QVERIFY(objects.objects()->at(2).at(0).y() == 22);
}
