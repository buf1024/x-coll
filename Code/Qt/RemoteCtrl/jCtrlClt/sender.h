#ifndef __48SLOTS_SENDER_H__
#define __48SLOTS_SENDER_H__

#include "ctrlcltsockthread.h"
#include <QAbstractSocket>

class SenderCtx
{
public:
};

class Sender
    : public SocketThread
{
    Q_OBJECT

public:
    Sender(QObject* parent = 0);
    ~Sender();

public:
    virtual void setSocket(QTcpSocket* sock);

public slots:
    void onContextInfoReady(SenderCtx* ctx);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
};


#endif /* __48SLOTS_SENDER_H__ */