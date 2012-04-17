#ifndef __48SLOTS_CTRL_SRV_H__
#define __48SLOTS_CTRL_SRV_H__

#include <QObject>

class SettingDlg;

class CtrlSrv
    : public QObject
{
    Q_OBJECT

public:
    CtrlSrv(QObject* parent = 0);
    ~CtrlSrv();

public:
    void start();

private:
    void initCtrlSrv();

private:
    SettingDlg* settingdlg;
};



#endif /* __48SLOTS_CTRL_SRV_H__ */

