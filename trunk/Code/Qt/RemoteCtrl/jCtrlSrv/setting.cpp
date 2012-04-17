#include "setting.h"
#include <QReadLocker>
#include <QSettings>


Setting::Setting()
{
    initDefaultSetting();
    restoreLastSetting();
}

Setting::Setting(const Setting&)
{
}

Setting& Setting::operator = (const Setting&)
{
}

Setting::~Setting()
{
}
Setting& Setting::instance()
{
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

int Setting::getBroadcasePort()
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

void Setting::initDefaultSetting()
{
    hostDesc = tr("");
    broadcastPort = DEFAULT_BROADCAST_PORT;
    listenPort = DEFAULT_LISTEN_PORT;
}

void Setting::restoreLastSetting()
{

}



































