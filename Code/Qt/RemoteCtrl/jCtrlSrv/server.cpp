#include "server.h"
#include "sender.h"
#include "receiver.h"

TcpServer::TcpServer(QObject* parent)
: QTcpServer(parent)
{

}
TcpServer::~TcpServer()
{

}
bool TcpServer::readyForNewConn()
{
    return true;
}
void TcpServer::refuseConn(int sf)
{

}
void TcpServer::initTcpServer()
{
    sender = new Sender(this);
    receiver = new Receiver(this);
}

void TcpServer::incomingConnection(int socketDescriptor)
{
    if (readyForNewConn()){
        if (receiver->isRunning()){
            receiver->exit();
        }
        if (sender->isRunning()){
            sender->exit();
        }

        receiver->start();
        sender->start();
    }else{
        refuseConn(socketDescriptor);
    }
}