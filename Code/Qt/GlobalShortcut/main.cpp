#include "mytestwidget.h"

int main(int argc, char** argv)
{
    CuteApp app(argc, argv);

    MyWidget widget;
    widget.show();

    return app.exec();
}
