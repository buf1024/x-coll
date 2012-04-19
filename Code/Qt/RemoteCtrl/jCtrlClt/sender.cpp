#include "sender.h"

Sender::Sender(QObject* parent)
: SocketThread(parent)
{

}
Sender::~Sender()
{

}

void Sender::onContextInfoReady(SenderCtx* ctx)
{

}

void Sender::setSocket(QTcpSocket* sock)
{

}

void Sender::onDisconnected()
{

}
void Sender::onError(QAbstractSocket::SocketError err)
{

}








