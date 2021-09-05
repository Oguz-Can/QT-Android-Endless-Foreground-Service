#include "budplogger.h"

BUdpLogger::BUdpLogger()
{
    qDebug() << "UDP logger initialization";
    // transmission setup, we don't expect any incoming data from here
    transmissionSocket = new QUdpSocket(this);
    qTransmissionIp = QHostAddress(ip);

    //reception setup
    receptionSocket = new QUdpSocket(this);
    qReceptionIp = QHostAddress(ip);
    receptionSocket->bind(qReceptionIp, receptionPort);

    //read setup
    connect(receptionSocket, &QUdpSocket::readyRead, this, &BUdpLogger::Reception);

    //GPS Service com test
    GPSInterface gpstester;
    connect(&gpstester, &GPSInterface::messageSender, this, &BUdpLogger::TxString);

//    //Periodic sender
//    connect (&updateTimer, &QTimer::timeout, this, &BUdpLogger::PeriodicSender);
//    updateTimer.start(1000);

//    QString LogString = QDateTime::currentDateTime().toString("dd-MMMM-yyyy hh:mm:ss");
//    QByteArray LogArray = LogString.toUtf8();

//    Transmission(LogArray);
//    PathCreator();
//    FileCreator();

}

void BUdpLogger::Transmission(QByteArray data){
    transmissionSocket->writeDatagram(data, qTransmissionIp, transmissionPort);
}

void BUdpLogger::TxString(QString log){
   Transmission(log.toUtf8());
}

void BUdpLogger::Reception (){
    QByteArray buffer;
    buffer.resize(receptionSocket->pendingDatagramSize());

    //TO DO:Call NULL pointers to readDatagram after debugging
    QHostAddress sender;
    quint16 senderPort;

    receptionSocket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

//    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    Log2Session(QString(buffer));
    //TO DO log buffer here
}

void BUdpLogger::PathCreator(){
    for(quint8 i = 0; i < paths.size(); i++){
        isSuccessful = Path.mkpath(paths[i]);
        if(isSuccessful){
            qDebug() << "Path created/already exists: " << paths[i];
        } else {
            qDebug() << "Path creation failed: " << paths[i];
            qDebug() << "Check storage permissions";
            break;
        }
    }
}

void BUdpLogger::FileCreator(){
    SessionLogFile.setFileName(filename);
    qDebug() << "Session file name: " << filename;
    qDebug() << "permissions: " << SessionLogFile.permissions();
    //qDebug() << "write other: " << SessionLogFile.setPermissions(QFileDevice::WriteOther);
    //qDebug() << "read other: " << SessionLogFile.setPermissions(QFileDevice::ReadOther);
    if (SessionLogFile.open(QIODevice::ReadWrite)){
        qDebug() << "Session file created";
    } else {
        qDebug() << "Could not create session file";
    }
}

bool BUdpLogger::Log2Session(QString log){
    if(!SessionLogFile.isOpen()){ //is file open
        if(SessionLogFile.open(QIODevice::ReadWrite)){ //can file can be opened
            return false; //probably no file permission
        }
    }
    QTextStream stream (&SessionLogFile);
    stream << log << endl;
    return true;
}

void BUdpLogger::PeriodicSender(){
    QString LogString = QDateTime::currentDateTime().toString("dd-MMMM-yyyy hh:mm:ss");
    QByteArray LogArray = LogString.toUtf8();

    Transmission(LogArray);
}
