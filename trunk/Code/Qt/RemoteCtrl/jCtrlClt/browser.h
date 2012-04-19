#ifndef __48SLOTS_BROWSER_H__
#define __48SLOTS_BROWSER_H__

#include <QTableWidget >
#include <QHash>

class Detecter;

class HostBrower
    : public QTableWidget
{
    Q_OBJECT
public:
    HostBrower(Detecter* deter, QWidget* parent = 0);
    ~HostBrower();
private:
    void initHostBrowser();
    void refresh(const QHash<QString, int>& hosts);

private slots:
    void onNewHostDetected(const QHash<QString, int>&);
    void onHostRemoved(const QHash<QString, int>&);
    void onCellDoubleClicked(int row, int column);

private:
    Detecter* detecter;
};

#endif /* __48SLOTS_BROWSER_H__ */















