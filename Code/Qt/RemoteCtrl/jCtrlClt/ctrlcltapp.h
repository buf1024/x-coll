#ifndef __48SLOTS_CTRL_CLT_APP_H__
#define __48SLOTS_CTRL_CLT_APP_H__

#include "cuteapp.h"


class CtrCltApp
    : public CuteApp
{
    Q_OBJECT

public:
    CtrCltApp(int argc, char** argv)
        : CuteApp(argc, argv)
    {
        setQuitOnLastWindowClosed(false);
    }
    ~CtrCltApp()
    {

    }
};

#endif /* __48SLOTS_CTRL_CLT_APP_H__ */
