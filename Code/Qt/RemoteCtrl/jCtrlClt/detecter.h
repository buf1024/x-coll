/*
 udp ���������������Ƿ����µĿ��ƶ˽��롣

 �ַ�����ʽ������������:������:IP:�˿�
 */

#ifndef __48SLOTS_DETECTER_H__
#define __48SLOTS_DETECTER_H__

#include <QThread>
#include <QHash>
#include <QReadWriteLock>


#define DEFAULT_DETECTER_TIMER 30
#define DEFAULT_BROADCAST_PORT 50203

class QTimer;
class QUdpSocket;


struct HostInfo
{
    QString hostDesc;
    QString hostName;
    QString hostIp;
    int     listenPort;
};

class Detecter
    : public QThread
{
    Q_OBJECT

public:
    Detecter(QObject* parent = 0);
    ~Detecter();

public:
    const QHash<QString, int>& getHostInfo();

private:
    void initDetecter();

signals:
    void newHostDetected(const QHash<QString, int>&, QString);
    void oldHostRemoved(const QHash<QString, int>&, QString);
    
private slots:
    void processPendingDatagrams();
    void onTimeOut();


private:
    QUdpSocket* udpSocket;

    QHash<QString, int> hostsInfo;

    QTimer* timerCheck;

    QReadWriteLock rdwrLock;
};


#endif /* __48SLOTS_DETECTER_H__ */

