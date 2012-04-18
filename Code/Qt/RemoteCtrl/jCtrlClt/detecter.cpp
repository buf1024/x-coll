#include "detecter.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QStringList>
#include <QTimer>


Detecter::Detecter(QObject* parent)
: QThread(parent)
{
    initDetecter();
}
Detecter::~Detecter()
{

}
void Detecter::initDetecter()
{
    timerCheck = new QTimer(this);
    connect(timerCheck, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(DEFAULT_BROADCAST_PORT, QUdpSocket::ShareAddress);
    QHostAddress groupAddress(QHostAddress::Broadcast);
    udpSocket->joinMulticastGroup(groupAddress);

    connect(udpSocket, SIGNAL(readyRead()),
        this, SLOT(processPendingDatagrams()));

    timerCheck->start(DEFAULT_DETECTER_TIMER*1000);
}
const QHash<QString, int>& Detecter::getHostInfo()
{
    QReadLocker locker(&rdwrLock);
    return hostsInfo;
}

 void Detecter::processPendingDatagrams()
 {
     while(udpSocket->hasPendingDatagrams()){
         QByteArray datagram;
         datagram.resize(udpSocket->pendingDatagramSize());
         udpSocket->readDatagram(datagram.data(), datagram.size());
         QString msg = datagram.data();
         
         if (hostsInfo.contains(msg)){
             hostsInfo[msg] += 1;
         }else{
             hostsInfo.insert(msg, 1);
             emit newHostDetected(hostsInfo, msg);
         }
         
     }
 }

 void Detecter::onTimeOut()
 {
     static unsigned long long timeoutcout = 0;
     timeoutcout++;

     QStringList strlist;

     QHashIterator<QString, int> it(hostsInfo);
     while(it.hasNext()){
         it.next();
         if (it.value() <= timeoutcout){
             strlist << it.key();
         }
     }
     QStringListIterator strit(strlist);
     while(strit.hasNext()){
         QString key = strit.next();
         hostsInfo.remove(key);
         emit oldHostRemoved(hostsInfo, key);
     }

 }



