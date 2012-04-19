

#ifndef __48SLOTS_RECEIVER_H__
#define __48SLOTS_RECEIVER_H__

#include "ctrlcltsockthread.h"
#include <QAbstractSocket>

class QImage;

class Receiver
    : public SocketThread
{
    Q_OBJECT

public:
    Receiver(QObject* parent = 0);
    ~Receiver();

signals:
    void receiverInfoReady(QImage*);

public:
    virtual void setSocket(QTcpSocket* sock);

public slots:
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
};


#endif /* __48SLOTS_RECEIVER_H__ */