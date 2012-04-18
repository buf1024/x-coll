#include "ctrlsrv.h"
#include "setting.h"
#include "settingdlg.h"
#include "ctrsrvapp.h"

#include "reporter.h"

CtrlSrv::CtrlSrv(QWidget* parent)
: QWidget(parent)
{
    initCtrlSrv();
}
CtrlSrv::~CtrlSrv()
{
    // remove hot key
    CtrSrvApp* app = dynamic_cast<CtrSrvApp*>(CtrSrvApp::instance()); 
    if (app){
        app->unregisterHotKey(this, DEFAULT_SETTINGDLG_HOTKEY_ID);
    }
}

void CtrlSrv::start()
{
    
}

void CtrlSrv::initCtrlSrv()
{
    settingdlg = NULL;

    // hot key
    CtrSrvApp* app = dynamic_cast<CtrSrvApp*>(CtrSrvApp::instance()); 
    if (app){
        app->registerHotKey(this, DEFAULT_SETTINGDLG_HOTKEY_ID,
            DEFAULT_SETTINGDLG_MODIFIER, DEFAULT_SETTINGDLG_VK);
        connect(app, SIGNAL(hotKeyGenerated(int, int, int)),
            this, SLOT(onHotKeyGenerated(int, int, int)));
    }

    // setting
    Setting::instance();

    reporter = new Reporter(this);
    reporter->start();
}

// slots
void CtrlSrv::onHotKeyGenerated(int id, int mod, int key)
{
    if (id == DEFAULT_SETTINGDLG_HOTKEY_ID){
        if (mod == DEFAULT_SETTINGDLG_MODIFIER &&
            key == DEFAULT_SETTINGDLG_VK){
                // settingdlg
                if (settingdlg == NULL){
                    settingdlg = new SettingDlg(this);

                    Qt::WindowFlags flag = settingdlg->windowFlags();
                    flag |= Qt::WindowStaysOnTopHint;
                    settingdlg->setWindowFlags(flag);
                }
                settingdlg->show();
        }

    }
}






















