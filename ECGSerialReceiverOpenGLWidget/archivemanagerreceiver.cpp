#include "archivemanagerreceiver.h"
#include <QDebug>
ArchiveManagerReceiver::ArchiveManagerReceiver(QObject *parent)
    : QObject{parent}
{
    //connect(&port, SIGNAL(started()), this, SLOT(recibir()));
    //connect(&port, SIGNAL(portError()), this, SLOT(errorPort()));
    connect(&port, SIGNAL(readyRead()), this, SLOT(readData()));
}

float ArchiveManagerReceiver::getDataAt(int p)
{
    return data[p];
}


void ArchiveManagerReceiver::startSerialCom(const QString &portn, QSerialPort::BaudRate baud)
{

    port.setBaudRate(baud);
    port.setStopBits(QSerialPort::TwoStop);
    port.setParity(QSerialPort::NoParity);
    port.setPortName(portn);
    port.open(QIODevice::ReadOnly);

    if (port.isOpen()){
        //buffer = (float*) malloc(100 * sizeof(float));
        emit started();
    }else{
        emit portError();
    }
}



void ArchiveManagerReceiver::readData()
{

    //qDebug() <<port.readAll();

    //int dataIndex = 0;
    float readDataV;
    buffer.clear();
    while(port.bytesAvailable()) {
        port.read((char*) &readDataV, sizeof(readDataV));
        buffer.append(QVariant(readDataV));
        data.append(readDataV);
    }
    //qDebug() << buffer[0];
    emit dataReceived(buffer);

}

void ArchiveManagerReceiver::errorPort()
{
    qDebug() << "ERROR PUERTO";
}
