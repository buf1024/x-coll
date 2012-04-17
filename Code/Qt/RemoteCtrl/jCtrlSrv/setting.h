/*
 ȫ���������ã�Ϊһ���������̻߳������
 */

#ifndef __48SLOTS_SETTING_H__
#define __48SLOTS_SETTING_H__

#include <QObject>
#include <QReadWriteLock>


#define DEFAULT_BROADCAST_PORT 50203 /* Ĭ�Ϲ㲥�˿� */
#define DEFAULT_LISTEN_PORT    50204 /* Ĭ�ϼ����˿� */

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
    QString hostDesc; // ��ǰ������Ϣ����
    int broadcastPort;// �㲥�˿�
    int listenPort;   // �����˿�


    QReadWriteLock rdwrLock; // ���߳�ͬ��
};


#endif /* __48SLOTS_SETTING_H__ */








