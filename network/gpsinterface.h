#ifndef GPSINTERFACE_H
#define GPSINTERFACE_H
#include <QDebug>
#include <QObject>
#include <QUdpSocket>
#include <QDataStream>
#include <QByteArray>

class GPSInterface : public QObject
{

    Q_OBJECT

public:
    GPSInterface();
private:
    //Reception setup
    QUdpSocket *receptionSock;
    const QString ip = "127.0.0.1";
    const quint16 receptionPort = 5555;
    QHostAddress qReceptionIp;

    void Reception();

signals:
    void messageSender(QString data);

public slots:
    void receptionHandler();

};

#endif // GPSINTERFACE_H
