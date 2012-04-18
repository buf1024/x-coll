#include "setting.h"
#include <QReadLocker>
#include <QSettings>


Setting::Setting()
{
    restoreLastSetting();
}

Setting::Setting(const Setting&)
{
}

Setting& Setting::operator = (const Setting&)
{
    return *this;
}

Setting::~Setting()
{
    saveSetting();
}
Setting& Setting::instance()
{
    static QReadWriteLock rdwrLock; // 多线程同步
    QReadLocker locker(&rdwrLock);
   
    static Setting setting;
    return setting;
}

QString Setting::getHostDesc()
{
    return hostDesc;
}
void Setting::setHostDesc(const QString& desc)
{    
    if (hostDesc != desc){
        hostDesc = desc;
        emit hostDescriptionChanged(hostDesc);
    }
}

int Setting::getBroadcastTimeValue()
{
    return broadcastTimeval;
}
void Setting::setBroadcastTimeValue(int timeval)
{
    if (broadcastTimeval != timeval) {
        broadcastTimeval = timeval;
        emit broadcastTimaeValueChanged(broadcastTimeval);
    }
}

int Setting::getBroadcastPort()
{
    return broadcastPort;
}
void Setting::setBroadcasePort(int port)
{
    if (broadcastPort != port){
        broadcastPort = port;
        emit broadcastPortChanged(broadcastPort);
    }
}

int Setting::getListenPort()
{
    return listenPort;
}

void Setting::setListenPort(int port)
{
    if (listenPort != port){
        listenPort = port;
        emit listenPortChanged(listenPort);
    }
    
}

void Setting::restoreLastSetting()
{
    QSettings setting(ORGANIZATION, APPLICATION);
    hostDesc = setting.value(HOST_DESC_KEY, DEFAULT_HOST_DESC).toString();
    broadcastPort = setting.value(BROADCAST_PORT_KEY, DEFAULT_BROADCAST_PORT).toInt();
    broadcastTimeval = setting.value(BROADCAST_TIME_KEY, DEFAULT_BROADCAST_TIME).toInt();
    listenPort = setting.value(LISTEN_PORT_KEY, DEFAULT_LISTEN_PORT).toInt();
}

void Setting::saveSetting()
{
    QSettings setting(ORGANIZATION, APPLICATION);
    setting.setValue(HOST_DESC_KEY, hostDesc);
    setting.setValue(BROADCAST_TIME_KEY, broadcastTimeval);
    setting.setValue(BROADCAST_PORT_KEY, broadcastPort);
    setting.setValue(LISTEN_PORT_KEY, listenPort);
    setting.sync();
}



































