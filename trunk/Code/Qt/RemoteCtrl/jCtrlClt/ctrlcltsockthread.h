

#ifndef __48SLOTS_CTRL_CLT_SOCKETTHREAD_H__
#define __48SLOTS_CTRL_CLT_SOCKETTHREAD_H__

#include <QThread>

class QTcpSocket;

class SocketThread
    : public QThread
{
    Q_OBJECT

public:
    SocketThread(QObject* parent = 0)
        : QThread(parent)
        , tcpSocket(NULL)
    {
    }
    ~SocketThread()
    {
    }

public:
    virtual void setSocket(QTcpSocket* sock)
    {
        tcpSocket = sock;
    }

protected:
    QTcpSocket* tcpSocket;
};


#endif /* __48SLOTS_CTRL_CLT_SOCKETTHREAD_H__ */