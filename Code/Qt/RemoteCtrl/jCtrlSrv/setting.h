/*
 ȫ���������ã�Ϊһ���������̻߳������
 */

#ifndef __48SLOTS_SETTING_H__
#define __48SLOTS_SETTING_H__

#include <QObject>
#include <QReadWriteLock>

#define DEFAULT_HOST_DESC      tr("")
#define DEFAULT_BROADCAST_TIME 1
#define DEFAULT_BROADCAST_PORT 50203 /* Ĭ�Ϲ㲥�˿� */
#define DEFAULT_LISTEN_PORT    50204 /* Ĭ�ϼ����˿� */

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
    // ���ɹ��죬���ɸ���
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
    QString hostDesc;               // ��ǰ������Ϣ����
    volatile int broadcastTimeval;  // �㲥ʱ����
    volatile int broadcastPort;     // �㲥�˿�
    volatile int listenPort;        // �����˿�

};


#endif /* __48SLOTS_SETTING_H__ */








