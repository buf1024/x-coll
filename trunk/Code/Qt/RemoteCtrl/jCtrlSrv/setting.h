/*
 全局数据配置，为一单件，多线程互斥访问
 */

#ifndef __48SLOTS_SETTING_H__
#define __48SLOTS_SETTING_H__

#include <QObject>
#include <QReadWriteLock>

#define DEFAULT_HOST_DESC      tr("")
#define DEFAULT_BROADCAST_TIME 1
#define DEFAULT_BROADCAST_PORT 50203 /* 默认广播端口 */
#define DEFAULT_LISTEN_PORT    50204 /* 默认监听端口 */

#define ORGANIZATION           tr("48slots")
#define APPLICATION            tr("RemoteCtrl.jCtrlSrv")

#define HOST_DESC_KEY          tr("HOST_DESC")
#define BROADCAST_TIME_KEY     tr("BROADCAST_TIME")
#define LISTEN_PORT_KEY        tr("LISTEN_PORT")
#define BROADCAST_PORT_KEY     tr("BROADCAST_PORT")

class Setting
    : public QObject
{
    Q_OBJECT
    // 不可构造，不可复制
private:
    Setting();
    Setting(const Setting& setting);
    Setting& operator = (const Setting&);

public:
    ~Setting();
    static Setting& instance();

public:
    void restoreLastSetting();
    void saveSetting();
    
    QString getHostDesc();
    void setHostDesc(const QString& desc);

    int getBroadcastTimeValue();
    void setBroadcastTimeValue(int timeval);

    int getBroadcastPort();
    void setBroadcasePort(int port);

    int getListenPort();
    void setListenPort(int port);

signals:
    void hostDescriptionChanged(const QString& hostDesc);
    void broadcastTimaeValueChanged(int time);
    void broadcastPortChanged(int port);
    void listenPortChanged(int port);

private:
    QString hostDesc;               // 当前主机信息描述
    volatile int broadcastTimeval;  // 广播时间间隔
    volatile int broadcastPort;     // 广播端口
    volatile int listenPort;        // 监听端口

};


#endif /* __48SLOTS_SETTING_H__ */








