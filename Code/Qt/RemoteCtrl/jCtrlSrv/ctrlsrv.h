#ifndef __48SLOTS_CTRL_SRV_H__
#define __48SLOTS_CTRL_SRV_H__

#include <QWidget>

#include "reporter.h"

class SettingDlg;
class Reporter;

#define DEFAULT_SETTINGDLG_HOTKEY_ID  1
#define DEFAULT_SETTINGDLG_MODIFIER   (MOD_ALT | MOD_CONTROL)
#define DEFAULT_SETTINGDLG_VK         VK_F12

class CtrlSrv
    : public QWidget
{
    Q_OBJECT

public:
    CtrlSrv(QWidget* parent = 0);
    ~CtrlSrv();

public:
    void start();

private:
    void initCtrlSrv();

private slots:
    void onHotKeyGenerated(int id, int mod, int key);
private:
    SettingDlg* settingdlg;

    Reporter* reporter;
};



#endif /* __48SLOTS_CTRL_SRV_H__ */

