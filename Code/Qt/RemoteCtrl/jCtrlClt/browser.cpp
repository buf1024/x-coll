#include "browser.h"
#include "detecter.h"

#include <QStringList>

#include <QMessageBox>

HostBrower::HostBrower(Detecter* deter, QWidget* parent)
: QTableWidget(parent)
, detecter(deter)
{
    initHostBrowser();
}
HostBrower::~HostBrower()
{

}

void HostBrower::initHostBrowser()
{
    // setup view
    QStringList headers;
    headers << tr("Host Name") << tr("IP Address")
        << tr("Listen Port") << tr("Description");
    
    setColumnCount(headers.count());
    setHorizontalHeaderLabels(headers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);    

    // setup detecter
    connect(detecter, SIGNAL(newHostDetected(const QHash<QString, int>&, QString)),
        this, SLOT(onNewHostDetected(const QHash<QString, int>&)));

    connect(detecter, SIGNAL(oldHostRemoved(const QHash<QString, int>&, QString)),
        this, SLOT(onHostRemoved(const QHash<QString, int>&)));

    connect(this, SIGNAL(cellDoubleClicked(int, int)),
        this, SLOT(onCellDoubleClicked(int, int)));

}

void HostBrower::refresh(const QHash<QString, int>& hosts)
{
    int row = rowCount();
    for (int i=0; i<=row; i++){
        removeRow(i);
    }
    QHashIterator<QString, int> it(hosts);
    while(it.hasNext()){
        it.next();
        QString host = it.key();
        QStringList hostlist = host.split(":");
        row = rowCount();
        insertRow(row);
        for (int i=0; i<hostlist.size(); i++){
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            item->setText(hostlist.at(i));
            setItem(row, i, item);
        }
    }
}

void HostBrower::onNewHostDetected(const QHash<QString, int>& hosts)
{
    refresh(hosts);
}

void HostBrower::onHostRemoved(const QHash<QString, int>& hosts)
{
    refresh(hosts);
}

void HostBrower::onCellDoubleClicked(int row, int column)
{
    QTableWidgetItem* itemX = item(row, 0);
    QString hostName = itemX->text();

    itemX = item(row, 1);
    QString hostIp = itemX->text();

    itemX = item(row, 2);
    int port = itemX->text().toInt();

}










