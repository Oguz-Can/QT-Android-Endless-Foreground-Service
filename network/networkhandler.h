#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H
#include <QObject>
#include "network/budplogger.h"
#include "network/gpsinterface.h"

/**
 * @brief This class should handle logging to app and GPS interface with the other service
 */
class NetworkHandler : public QObject
{
    Q_OBJECT

public:
    NetworkHandler();
private:
    BUdpLogger DebugLogger;
    GPSInterface GPSLogger;

public slots:
    void Log(QString message);
};

#endif // NETWORKHANDLER_H
