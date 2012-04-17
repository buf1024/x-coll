/*
 全局数据配置，为一单件，多线程互斥访问
 */

#ifndef __48SLOTS_SETTING_H__
#define __48SLOTS_SETTING_H__

#include <QObject>
#include <QReadWriteLock>


#define DEFAULT_BROADCAST_PORT 50203 /* 默认广播端口 */
#define DEFAULT_LISTEN_PORT    50204 /* 默认监听端口 */

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
    Setting& instance();

public:
    QString getHostDesc();
    void setHostDesc(const QString& desc);

    int getBroadcasePort();
    void setBroadcasePort(int port);

    int getListenPort();
    void setListenPort(int port);

signals:
    void hostDescriptionChanged(const QString& hostDesc);
    void broadcastPortChanged(int port);
    void listenPortChanged(int port);

private:
    void initDefaultSetting();
    void restoreLastSetting();

private:
    QString hostDesc; // 当前主机信息描述
    int broadcastPort;// 广播端口
    int listenPort;   // 监听端口


    QReadWriteLock rdwrLock; // 多线程同步
};


#endif /* __48SLOTS_SETTING_H__ */








