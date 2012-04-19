#include "ctrlclt.h"
#include "detecter.h"
#include "receiver.h"
#include "sender.h"
#include "connectdlg.h"

#include <QApplication>
#include <QtGui>
#include <QtNetwork>

CtrlCtl::CtrlCtl(QWidget* parent)
: QWidget(parent)
{
    initCtrlClt();
}
CtrlCtl::~CtrlCtl()
{
    // remove hot key
    //CtrSrvApp* app = dynamic_cast<CtrSrvApp*>(CtrSrvApp::instance()); 
    //if (app){
    //    app->unregisterHotKey(this, DEFAULT_SETTINGDLG_HOTKEY_ID);
    //}
}

void CtrlCtl::initCtrlClt()
{
    // mouse tracking
    setMouseTracking(true);



    // hot key
    //CtrCltApp* app = dynamic_cast<CtrCltApp*>(CtrSrvApp::instance()); 
    //if (app){
    //    app->registerHotKey(this, DEFAULT_SETTINGDLG_HOTKEY_ID,
    //        DEFAULT_SETTINGDLG_MODIFIER, DEFAULT_SETTINGDLG_VK);
    //    connect(app, SIGNAL(hotKeyGenerated(int, int, int)),
    //        this, SLOT(onHotKeyGenerated(int, int, int)));
    //}


//    detecter = new Detecter;
//    hostBrowser = new HostBrower(detecter, 0);
//    detecter->start();
//    hostBrowser->show();


    // network
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()),
        this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(disconnected()),
        this, SLOT(onDisonnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(onError(QAbstractSocket::SocketError)));
    
    sender = new Sender(this);
    sender->setSocket(tcpSocket);
    connect(this, SIGNAL(contextInfoReady(SenderCtx*)),
        sender, SLOT(onContextInfoReady(SenderCtx*)));

    receiver = new Receiver(this);
    connect(receiver, SIGNAL(receiverInfoReady(QImage*)),
        this, SLOT(onReceiverInfoReady(QImage*)));
    receiver->setSocket(tcpSocket);


    // trayicon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/res/jCtrlClt.ico"));
    QString tooltip = ORGANIZATION;
    tooltip += tr(" ");
    tooltip += APPLICATION;
    trayIcon->setToolTip(tooltip);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), 
        this, SLOT(onQuitAction()));
    browserAction = new QAction(tr("&Browser"), this);
    connect(browserAction, SIGNAL(triggered()), 
        this, SLOT(onBrowserAction()));
    optAction = new QAction(tr("&Option"), this);
    connect(optAction, SIGNAL(triggered()), 
        this, SLOT(onOptAction()));
    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), 
        this, SLOT(onAboutAction()));
    connectAction = new QAction(tr("&Connect..."), this);
    connect(connectAction, SIGNAL(triggered()), 
        this, SLOT(onConnectAction()));
    visableAction = new QAction(tr("&Hide"), this);
    connect(visableAction, SIGNAL(triggered()), 
        this, SLOT(onVisableAction()));

    QMenu* trayMenu = new QMenu(this);
    trayMenu->addAction(aboutAction);
    QAction* sep = new QAction(this);
    sep->setSeparator(true);
    trayMenu->addAction(sep);
    trayMenu->addAction(visableAction);
    sep = new QAction(this);
    sep->setSeparator(true);
    trayMenu->addAction(sep);
    trayMenu->addAction(optAction);
    trayMenu->addAction(browserAction);
    trayMenu->addAction(connectAction);
    sep = new QAction(this);
    sep->setSeparator(true);
    trayMenu->addAction(sep);
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);

}
void CtrlCtl::start()
{     
    // center
    QSize desktopSize = QApplication::desktop()->size();
    int w = desktopSize.width()/2;
    int h = desktopSize.height()/2;
    int x = (desktopSize.width() - w) / 2;
    int y = (desktopSize.height() - h) / 2;
    setGeometry(x, y, w, h);
    show();
    trayIcon->show();
    QString msg = APPLICATION;
    msg += tr(" Is Running...");
    QString title = APPLICATION;
    trayIcon->showMessage(title, msg);
}


void CtrlCtl::inputMethodEvent(QInputMethodEvent* event)
{

}
void CtrlCtl::keyPressEvent(QKeyEvent* event)
{

}
void CtrlCtl::keyReleaseEvent(QKeyEvent* event)
{

}
void CtrlCtl::mouseDoubleClickEvent(QMouseEvent* event)
{

}
void CtrlCtl::mouseMoveEvent(QMouseEvent* event)
{

}
void CtrlCtl::mousePressEvent(QMouseEvent* event)
{

}
void CtrlCtl::mouseReleaseEvent(QMouseEvent* event)
{

}
void CtrlCtl::wheelEvent(QWheelEvent* event)
{

}
void CtrlCtl::paintEvent(QPaintEvent* event)
{

    static QImage img = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();

    QSize s = size();
    QImage newimg = img.scaled(s);

    QPainter painter(this);
    painter.drawImage(0, 0, newimg);
}

void CtrlCtl::onConnected()
{
    sender->start();
    receiver->start();
}

void  CtrlCtl::onDisconnected()
{

}
void CtrlCtl::onError(QAbstractSocket::SocketError err)
{
    
}


void CtrlCtl::onReceiverInfoReady(QImage* img)
{

}

void CtrlCtl::onQuitAction()
{
    emit aboutToQuit();

    if (sender->isRunning()){
        sender->wait();
    }
    if (receiver->isRunning()){
        receiver->wait();
    }

    QCoreApplication* app = QApplication::instance();
    app->quit();
}
void CtrlCtl::onAboutAction()
{
    QMessageBox::about(this,
        APPLICATION, tr("buf1024@gmail.com"));
}
void CtrlCtl::onVisableAction()
{
    if (isHidden()){
        visableAction->setText(tr("&Hide"));
        show();
    }else{
        visableAction->setText(tr("&Show"));
        hide();
    }
}
void CtrlCtl::onOptAction()
{

}
void CtrlCtl::onBrowserAction()
{

}

void CtrlCtl::onConnectAction()
{
    ConnectDlg dlg;
    if (dlg.exec() == QDialog::Accepted){
        QString host = dlg.getHostAddress();
        int port = dlg.getHostPort().toInt();
        // ignore
        QString key = dlg.getExchangeKey();

        tcpSocket->connectToHost(host, port);
    }
}



