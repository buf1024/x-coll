/*

 UDP�������̣߳����ڱ��浱ǰ������׼��״̬�����㲥��ǰ������Ϣ 

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
    QTimer* timer;           // ��ʱ��
    QUdpSocket* udpSocket;   // udp socket
    QHostAddress* hostAddr;  // �㲥��ַ

    QString hostDesc;        // �㲥��������
};

#endif /* __48SLOTS_REPORTER_H__ */



