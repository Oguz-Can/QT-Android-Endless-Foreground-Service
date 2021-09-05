#include <QAndroidService>
#include "network/networkhandler.h"

int main(int argc, char *argv[])
{
    QAndroidService app(argc, argv);

    NetworkHandler networkobj;
    networkobj.Log("Service initialized");

    return app.exec();
}
