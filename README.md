# Use carefully lambda function with Qt's connections

Qt 5 introduce a new signal-slo connect syntaxe, using pointers to function.
This connect can be used with C++11 lambda function.

Usualy, a connection is destroyed automatically when sender or receiver object
is deleted. But with connect to lambda function, the connect is destroy only 
when sender is deleted, not receiver.

If a raw pointer is captured inside lambda function, it's not possible to
check if object is deleted or not (dangling pointer). It's a good practice
to avoid passing a pointer by value in lambda (by passing a pointer, or this,
or everything by default [=]). (See "Effective Modern C++", Scott Meyers, Item 
31).

This project run test to show this problem. This is a example of output I obtains (Qt 5.4.2, MSVC 2013) :

```
********* Start testing of ConnectLambdaTest *********
Config: Using QtTest library 5.4.2, Qt 5.4.2 (i386-little_endian-ilp32 shared (dynamic) debug build; by MSVC 2013)
PASS   : ConnectLambdaTest::initTestCase()
QDEBUG : ConnectLambdaTest::testCaseNormalUse() Object::setCheckValue 0x58ef
PASS   : ConnectLambdaTest::testCaseNormalUse()
QDEBUG : ConnectLambdaTest::testCaseWithLambda() Object::setCheckValue 0xb69d
PASS   : ConnectLambdaTest::testCaseWithLambda()
QDEBUG : ConnectLambdaTest::testCaseLambdaAndDeletedObject() Object::setCheckValue 0x2d9b
FAIL!  : ConnectLambdaTest::testCaseLambdaAndDeletedObject() This test need to fail...
..\untitled\tst_connectlambdatest.cpp(86) : failure location
QFATAL : ConnectLambdaTest::testCaseLambdaQPointer() ASSERT: "receiver" in file tst_connectlambdatest.cpp, line 107
FAIL!  : ConnectLambdaTest::testCaseLambdaQPointer() Received a fatal error.
Unknown file(0) : failure location
Totals: 3 passed, 2 failed, 0 skipped, 0 blacklisted
********* Finished testing of ConnectLambdaTest *********
```

I recommand to use lambda only when you are sure the sender is deleted when receiver is deleted too. 
For example, connect only QObject and his children. And use QPointer to capture pointer inside lambda 
function.

And of course: "Always check your pointers!"
