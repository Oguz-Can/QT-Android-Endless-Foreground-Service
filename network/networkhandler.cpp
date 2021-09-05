#include "networkhandler.h"

NetworkHandler::NetworkHandler()
{
    DebugLogger.TxString("Network Handler initialzing");
    connect(&GPSLogger, &GPSInterface::messageSender, &DebugLogger, &BUdpLogger::TxString);
    DebugLogger.TxString("Network Handler initialzed");
}

void NetworkHandler::Log(QString message){
    DebugLogger.TxString(message);
}
