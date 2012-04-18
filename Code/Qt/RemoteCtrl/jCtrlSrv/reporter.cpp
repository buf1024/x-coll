#include "reporter.h"
#include "setting.h"
#include <QTimer>
#include <QUdpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QByteArray>

#include <QWidget>

Reporter::Reporter(QObject* parent)
: QThread(parent)
{
    initReporter();
}
Reporter::~Reporter()
{

}

void Reporter::initReporter()
{
    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);
    
    Setting& setting = Setting::instance();
    
    hostDesc = setting.getHostDesc();
    timeInterval = setting.getBroadcastTimeValue();
    broadcastPort = setting.getBroadcastPort();
    listenPort = setting.getListenPort();

    timer->setInterval(timeInterval*1000);

    connect(&setting, SIGNAL(hostDescriptionChanged(const QString&)),
        this, SLOT(onHostDescChanged(const QString&)));
    connect(&setting, SIGNAL(broadcastTimaeValueChanged(int)),
        this, SLOT(onTimerChanged(int)));
    connect(&setting, SIGNAL(broadcastPortChanged(int)),
        this, SLOT(onBroadcastPortChanged(int)));

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    stopThread = false;

    timer->start();

}

void Reporter::sendDiagram()
{
    QString msg;
    
    msg += hostDesc + ":";
    msg += QHostInfo::localHostName() + ":";
    msg += hostIp + ":";
    msg += QString::number(listenPort);

    QByteArray diagram = msg.toAscii();

    static QHostAddress broadcastHost(QHostAddress::Broadcast);

    udpSocket->writeDatagram(diagram.data(), diagram.size(), broadcastHost, broadcastPort);
}
void Reporter::getHostIp()
{
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
    QHostAddress addr = info.addresses().first();
    hostIp = addr.toString();
}
void Reporter::onTimerChanged(int newtime)
{
    timeInterval = newtime;
    timer->setInterval(timeInterval);
    timer->start();
}
void Reporter::onBroadcastPortChanged(int newport)
{
    broadcastPort = newport;
}
void Reporter::onListenPortChanged(int newport)
{
    listenPort = newport;
}
void Reporter::onHostDescChanged(const QString& desc)
{
    hostDesc = desc;
}
void Reporter::onTimeout()
{
    if (!stopThread){
        sendDiagram();
    }else{
        this->exit();
    }
    
}












