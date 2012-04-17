/*

 UDP服务器线程，用于报告当前服务处于准备状态，并广播当前机器信息 

 */

#ifndef __48SLOTS_REPORTER_H__
#define __48SLOTS_REPORTER_H__

#include <QThread>

class QTimer;
class QUdpSocket;
class QHostAddress;

class Reporter
    : QThread
{
    Q_OBJECT

public:
    Reporter(QObject* parent = 0);
    ~Reporter();

protected:
    virtual void run();

private:
    QTimer* timer;           // 计时器
    QUdpSocket* udpSocket;   // udp socket
    QHostAddress* hostAddr;  // 广播地址

    QString hostDesc;        // 广播主机描述
};

#endif /* __48SLOTS_REPORTER_H__ */



