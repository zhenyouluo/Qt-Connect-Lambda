#include "object.h"
#include <QDebug>

Object::Object(QObject *parent) : QObject(parent) {
}

void Object::emitSignal(int value) {
  emit signalTest(value);
}

void Object::setCheckValue(int value) {
  m_checkValue = value;
  qDebug() << __FUNCTION__ << showbase << hex << value;
}

int Object::checkValue() const {
  return m_checkValue;
}

void Object::slotTest(int value) {
  setCheckValue(value);
}
