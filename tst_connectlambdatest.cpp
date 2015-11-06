#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "object.h"

class ConnectLambdaTest : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(ConnectLambdaTest)

public:
  ConnectLambdaTest() = default;

private Q_SLOTS:
  void testCaseNormalUse();
  void testCaseWithLambda();
  void testCaseLambdaAndDeletedObject();
  void testCaseLambdaQPointer();
};

/*!
 * \brief Qt5's signal and slot connection, using pointer to member functions.
 */
void ConnectLambdaTest::testCaseNormalUse() {
  // create sender and receiver objects
  QScopedPointer<Object> sender ( new Object );
  QScopedPointer<Object> receiver ( new Object );

  // connect them
  connect(sender.data(), &Object::signalTest, receiver.data(), &Object::slotTest);

  // emit signal
  sender->emitSignal(0x58ef);

  // test if slot correclty receive info
  QCOMPARE(0x58ef, receiver->checkValue());
}

/*!
 * \brief Use lambda with Qt5's new connection syntaxe.
 */
void ConnectLambdaTest::testCaseWithLambda() {
  // create sender and receiver objects
  // receiver is shared with lambda context
  QScopedPointer<Object> sender ( new Object );
  QSharedPointer<Object> receiver ( new Object );

  // connect them with lambda
  connect(sender.data(), &Object::signalTest,
          [receiver](int value){ Q_ASSERT(receiver); receiver->setCheckValue(value); });

  // emit signal
  sender->emitSignal(0xb69d);

  // test if slot correclty receive info
  QCOMPARE(0xb69d, receiver->checkValue());
}

/*!
 * \brief Use lambda with Qt5's new connection syntaxe, with invalide pointer.
 * The raw pointer become invlide inside the lambda, but the connect is not
 * destroy when receiver is deleted. Then, emitting signal call lambda
 * with this invalid pointer, and cause a Undefined Behavior (UB).
 *
 * Note: UB doesn't cause crash every time. When I run this tests (MingW 4.9.2
 * and MSVC 2013), the test run like object is valid.
 */
void ConnectLambdaTest::testCaseLambdaAndDeletedObject() {
  // create sender and receiver objects
  // we want to delete receiver before end of function, the use raw pointer
  QScopedPointer<Object> sender ( new Object );
  Object* receiver ( new Object );

  // connect them with lambda
  connect(sender.data(), &Object::signalTest,
          [receiver](int value){ Q_ASSERT(receiver); receiver->setCheckValue(value); });

  // delete receiver
  delete receiver;
  receiver = nullptr;

  // emit signal
  sender->emitSignal(0x2d9b);

  // can't test, receiver is nullptr
  // QCOMPARE(0x800a, receiver->checkValue());
  QFAIL("This test need to fail...");
}

/*!
 * \brief Use QPointer to check pointer in lambda.
 * QPointer is Qt's smart pointer, which become nullptr when
 * QObject's derived object is deleted. QPointer is copiable,
 * then when can copy it directly inside lambda.
 *
 * In lambda, we can just check pointer with assert, if the receiver
 * can have a shorter lifetime than sender, or 'if' statement if
 * receiver need to have a longer lifetime than sender.
 */
void ConnectLambdaTest::testCaseLambdaQPointer() {
  // create sender and receiver objects
  // use QPointer to check pointer before use
  QScopedPointer<Object> sender ( new Object );
  QPointer<Object> receiver ( new Object );

  // connect them with lambda
  connect(sender.data(), &Object::signalTest,
          [receiver](int value){ Q_ASSERT(receiver); receiver->setCheckValue(value); });

  // delete receiver
  delete receiver;

  // emit signal
  sender->emitSignal(0x800a);

  // can't test, receiver is nullptr
  // QCOMPARE(0x800a, receiver->checkValue());
  QFAIL("This test need to fail...");
}

QTEST_MAIN(ConnectLambdaTest)

#include "tst_connectlambdatest.moc"
