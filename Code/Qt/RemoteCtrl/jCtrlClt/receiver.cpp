#include "receiver.h"



Receiver::Receiver(QObject* parent)
: SocketThread(parent)
{

}
Receiver::~Receiver()
{

}

void Receiver::setSocket(QTcpSocket* sock)
{

}



void Receiver::onDisconnected()
{

}
void Receiver::onError(QAbstractSocket::SocketError err)
{

}



