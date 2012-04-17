
#include <QApplication>
#include "ctrlclt.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    CtrlCtl clt;
    clt.show();

    return app.exec();
}


