#ifndef __48SLOTS_CTRL_SRV_APP_H__
#define __48SLOTS_CTRL_SRV_APP_H__

#include "cuteapp.h"


class CtrSrvApp
    : public CuteApp
{
    Q_OBJECT

public:
    CtrSrvApp(int argc, char** argv)
        : CuteApp(argc, argv)
    {

    }
    ~CtrSrvApp()
    {

    }
};

#endif /* __48SLOTS_CTRL_SRV_APP_H__ */
