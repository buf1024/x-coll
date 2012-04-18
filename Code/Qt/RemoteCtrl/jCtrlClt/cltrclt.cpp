#include "ctrlclt.h"
#include "detecter.h"

CtrlCtl::CtrlCtl(QWidget* parent)
: QWidget(parent)
{
    initCtrlClt();
}
CtrlCtl::~CtrlCtl()
{

}

void CtrlCtl::initCtrlClt()
{
    detecter = new Detecter(this);
    connect(detecter, SIGNAL(newHostDetected(const QHash<QString, int>&, QString)),
        this, SLOT(newHostDetected(const QHash<QString, int>&, QString)));
    detecter->start();
}
void CtrlCtl::start()
{
    show();
}

void CtrlCtl::newHostDetected(const QHash<QString, int>& host, QString msg)
{
    QString title = msg + QString::number(host[msg]);
    setWindowTitle(title);
}