#ifndef __48SLOTS_CONNECT_DLG_H__
#define __48SLOTS_CONNECT_DLG_H__

#include <QDialog>

class ConnectDlg
    : public QDialog
{
    Q_OBJECT

public:
    ConnectDlg(QWidget* parent = 0);
    ~ConnectDlg();

public:
    QString getHostAddress();
    QString getHostPort();
    QString getExchangeKey();
};


#endif /* __48SLOTS_CONNECT_DLG_H__ */






























