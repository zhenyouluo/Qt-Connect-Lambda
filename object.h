#ifndef id_5e22f6e593896b7b2b508b9a4bb35c15f2af7ea3_H
#define id_5e22f6e593896b7b2b508b9a4bb35c15f2af7ea3_H

#include <QObject>

class Object : public QObject {
  Q_OBJECT
public:
  explicit Object(QObject *parent = 0);

  void emitSignal(int);

  void setCheckValue(int);
  int checkValue() const;

signals:
  void signalTest(int);

public slots:
  void slotTest(int);

private:
  int m_checkValue{};
};

#endif // id_5e22f6e593896b7b2b508b9a4bb35c15f2af7ea3_H
