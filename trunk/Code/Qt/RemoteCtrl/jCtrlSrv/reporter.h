/*

 UDP�������̣߳����ڱ��浱ǰ������׼��״̬�����㲥��ǰ������Ϣ 

 */

#ifndef __48SLOTS_REPORTER_H__
#define __48SLOTS_REPORTER_H__

#include <QThread>

class QTimer;
class QUdpSocket;
class QHostAddress;

class QWidget;

class Reporter
    : public QThread
{
    Q_OBJECT

public:
    Reporter(QObject* parent = 0);
    ~Reporter();

private:
    void initReporter();
    void getHostIp();
    void sendDiagram();

public slots:
    void onTimerChanged(int newtime);
    void onBroadcastPortChanged(int newport);
    void onListenPortChanged(int newport);
    void onHostDescChanged(const QString& desc);
    void onTimeout();

private:
    QTimer* timer;           // ��ʱ��
    QUdpSocket* udpSocket;   // udp socket
    
    QString hostDesc;
    int timeInterval;
    int broadcastPort;
    int listenPort;

    QString hostIp;

    bool stopThread;
};

#endif /* __48SLOTS_REPORTER_H__ */



