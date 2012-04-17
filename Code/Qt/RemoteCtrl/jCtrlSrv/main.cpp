#include "ctrsrvapp.h"
#include "ctrlsrv.h"

int main(int argc, char** argv)
{
    CtrSrvApp app(argc, argv);

    CtrlSrv srv;
    srv.start();

    return app.exec();
}


