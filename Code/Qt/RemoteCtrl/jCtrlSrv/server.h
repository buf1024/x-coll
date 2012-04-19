#ifndef __48SLOTS_CTRL_SRV_H__
#define __48SLOTS_CTRL_SRV_H__

#include <QTcpServer>


class Receiver;
class Sender;

class TcpServer
    : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject* parent = 0);
    ~TcpServer();

public:
    bool readyForNewConn();
    void refuseConn(int sf);

private:
    void initTcpServer();

protected:
    virtual void incomingConnection(int socketDescriptor);

private:
    Receiver* receiver;
    Sender* sender;
};


#endif /* __48SLOTS_CTRL_SRV_H__ */















