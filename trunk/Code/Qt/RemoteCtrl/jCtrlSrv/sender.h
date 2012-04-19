#ifndef __48SLOTS_SENDER_H__
#define __48SLOTS_SENDER_H__

#include <QThread>

class QTcpSocket;

class Sender
    : public QThread
{
    Q_OBJECT

public:
    Sender(QObject* parent = 0);
    ~Sender();
};


#endif /* __48SLOTS_SENDER_H__ */




