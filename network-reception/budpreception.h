#ifndef BUDPRECEPTION_H
#define BUDPRECEPTION_H
#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QTimer>
#include <QByteArray>

class BUdpReception : public QObject
{
    Q_OBJECT
public:
    BUdpReception();
    void Transmission (QByteArray data); //Send data to service
private:
    //transmission
    QUdpSocket *transmissionSocket;
    const QString ip = "127.0.0.1";
    const quint16 transmissionPort = 8585;
    QHostAddress qTransmissionIp;
    //reception
    QUdpSocket *receptionSocket;
    const quint16 receptionPort = 9999;
    QHostAddress qReceptionIp;
    void Reception();
    //path and file creation
    QFile SessionLogFile;
    QString SessionLogsPath = "/sdcard/ATOK/SessionLogs/";
    QDir Path;
    QStringList paths = {SessionLogsPath};//Add paths to create here
    bool isSuccessful;
    QString CurrentDateFileName = QDateTime::currentDateTime().toString("dd-MMMM-yyyy hh:mm:ss") + " " + "ForegroundLog.txt"; //Record initialization time
    QString filename = SessionLogsPath + CurrentDateFileName;
    void PathCreator();
    void FileCreator();
    //write to file
    bool Log2Session(QString log);
    QTimer updateTimer;

public slots:
    void PeriodicSender();

signals:
    void onLog(QString log);
};

#endif // BUDPRECEPTION_H
