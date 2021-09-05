#include "gpsinterface.h"

GPSInterface::GPSInterface()
{
    emit messageSender("GPS Interface Initilization");
    //init reception sock
    receptionSock = new QUdpSocket(this);
    qReceptionIp = QHostAddress(ip);
    receptionSock->bind(qReceptionIp, receptionPort);

    //read setup
    connect(receptionSock, &QUdpSocket::readyRead, this, &GPSInterface::receptionHandler);

    emit messageSender("GPS Interface Initilized");
}

void GPSInterface::receptionHandler(){
    //buffer setup
        QByteArray buffer;
        buffer.resize(receptionSock->pendingDatagramSize());
        //read sock buffer
        receptionSock->readDatagram(buffer.data(), buffer.size(), nullptr, nullptr);
        //convert to 3 doubles
        if(buffer.size()!=24){
            emit messageSender("unexpected packet size: " + QString::number(buffer.size()));
        } else {
            QByteArray qbLat;
            for(quint8 i = 0; i < 8; i++){
                qbLat.append(buffer[i]);
            }
            QDataStream StreamLat(qbLat);
            double Lat;
            StreamLat >> Lat;

            QByteArray qbLon;
            for(quint8 i = 8; i < 16; i++){
                qbLon.append(buffer[i]);
            }
            QDataStream StreamLon(qbLon);
            double Lon;
            StreamLon >> Lon;

            QByteArray qbAlt;
            for(quint8 i = 16; i < 24; i++){
                qbAlt.append(buffer[i]);
            }
            QDataStream StreamAlt(qbAlt);
            double Alt;
            StreamAlt >> Alt;

            emit messageSender("Lat: " + QString::number(Lat) + " Lon: " +  QString::number(Lon) + " Alt: " +  QString::number(Alt));
        }
}
