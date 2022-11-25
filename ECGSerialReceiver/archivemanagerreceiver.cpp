#include "archivemanagerreceiver.h"
#include <QDebug>
ArchiveManagerReceiver::ArchiveManagerReceiver(QObject *parent)
    : QObject{parent}
{
    //connect(&port, SIGNAL(started()), this, SLOT(recibir()));
    //connect(&port, SIGNAL(portError()), this, SLOT(errorPort()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(recibir()));
}

void ArchiveManagerReceiver::startSerialCom(const QString &portn, QSerialPort::BaudRate baud)
{

    port.setBaudRate(baud);
    port.setStopBits(QSerialPort::TwoStop);
    port.setParity(QSerialPort::NoParity);
    port.setPortName(portn);
    port.open(QIODevice::ReadOnly);

    //if (port.isOpen()){
    //    buffer = (float*) malloc(100 * sizeof(float));
    //    //emit started();
    //}else{
    //    //emit portError();
    //}
}

void ArchiveManagerReceiver::stopSerialCom()
{

}

void ArchiveManagerReceiver::recibir()
{

    //float readData;
    //while(port.bytesAvailable()){
    //    port.read((char*)&readData, sizeof(readData));
    //}
    qDebug() <<port.readAll();

}

void ArchiveManagerReceiver::startTimer(int n)
{
    timer.start(n);
}

void ArchiveManagerReceiver::errorPort()
{
    qDebug() << "ERROR PUERTO";
}
