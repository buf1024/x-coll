#ifndef __48SLOTS_RECEIVER_H__
#define __48SLOTS_RECEIVER_H__

#include <QThread>

class Receiver
    : public QThread
{
    Q_OBJECT

public:
    Receiver(QObject* parent = 0);
    ~Receiver();
};


#endif /* __48SLOTS_RECEIVER_H__ */