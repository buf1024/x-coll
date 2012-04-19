/*
 客户端主功能
 */

#ifndef __48SLOTS_CTRL_CLT_H__
#define __48SLOTS_CTRL_CLT_H__

#include <QWidget>
#include <QAbstractSocket>


//#define DEFAULT_OPTION_HOTKEY_ID  100
//#define DEFAULT_OPTION_MODIFIER   (MOD_ALT | MOD_CONTROL)
//#define DEFAULT_OPTION_VK         VK_F11

// class HostBrower;

class Detecter;

class QTcpSocket;
class Receiver;
class Sender;
class SenderCtx;

class QInputMethodEvent;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;
class QPaintEvent;

class CtrlCtl
    : public QWidget
{
    Q_OBJECT

public:
    CtrlCtl(QWidget* parent = 0);
    ~CtrlCtl();

public:
    void start();

protected:
    virtual void inputMethodEvent(QInputMethodEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void paintEvent(QPaintEvent* event);

    
public slots:
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);
    void onReceiverInfoReady(QImage* img);

signals:
    void contextInfoReady(SenderCtx*);

private:
    void initCtrlClt();

private:
//    HostBrower* hostBrowser;

//    Detecter* detecter;

    QTcpSocket* tcpSocket;

    Sender* sender;          // send thread
    Receiver* receiver;      // read thread
};

#endif /* __48SLOTS_CTRL_CLT_H__ */

