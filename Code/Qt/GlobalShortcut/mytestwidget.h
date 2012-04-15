#include "cuteapp.h"
class MyWidget
    : public QWidget
{
    Q_OBJECT


public:
    MyWidget()
    {
        CuteApp* app = (CuteApp*)qApp;
        app->registerHotKey(this, 1, MOD_ALT | MOD_CONTROL, VK_F12);
        connect(app, SIGNAL(hotKeyGenerated(int, int, int)),
            this, SLOT(onhotkey(int, int, int)));
    }
    ~MyWidget()
    {
        CuteApp* app = (CuteApp*)qApp;
        app->unregisterHotKey(this, 1);
    }
    public slots:
        void onhotkey(int id, int md, int vk){
            qApp->aboutQt();
        }
};
