#include "budpreception.h"

BUdpReception::BUdpReception()
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
    connect(receptionSocket, &QUdpSocket::readyRead, this, &BUdpReception::Reception);

//    //Periodic sender
//    connect (&updateTimer, &QTimer::timeout, this, &BUdpReception::PeriodicSender);
//    updateTimer.start(1000);

//    QString LogString = QDateTime::currentDateTime().toString("dd-MMMM-yyyy hh:mm:ss");
//    QByteArray LogArray = LogString.toUtf8();

//    Transmission(LogArray);
//    PathCreator();
//    FileCreator();
 qDebug() << "UDP logger initialized";
}

void BUdpReception::Transmission(QByteArray data){
    transmissionSocket->writeDatagram(data, qTransmissionIp, transmissionPort);
}

void BUdpReception::Reception (){
    QByteArray buffer;
    buffer.resize(receptionSocket->pendingDatagramSize());

    //TO DO:Call NULL pointers to readDatagram after confirming transmission
    QHostAddress sender;
    quint16 senderPort;

    receptionSocket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

//    qDebug() << "Message from: " << sender.toString();
//    qDebug() << "Message port: " << senderPort;
    qDebug() << "[LocalLog]: " << buffer;
    emit onLog(buffer);
//    Log2Session(QString(buffer));
    //TO DO log buffer here
}

void BUdpReception::PathCreator(){
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

void BUdpReception::FileCreator(){
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

bool BUdpReception::Log2Session(QString log){
    if(!SessionLogFile.isOpen()){ //is file open
        if(SessionLogFile.open(QIODevice::ReadWrite)){ //can file can be opened
            return false; //probably no file permission
        }
    }
    QTextStream stream (&SessionLogFile);
    stream << log << endl;
    return true;
}

void BUdpReception::PeriodicSender(){
    QString LogString = QDateTime::currentDateTime().toString("dd-MMMM-yyyy hh:mm:ss");
    QByteArray LogArray = LogString.toUtf8();

    Transmission(LogArray);
}

