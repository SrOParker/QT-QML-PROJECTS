#include "serialcommunicator.h"

#include <QDebug>
SerialCommunicator::SerialCommunicator(QObject *parent)
    : QObject{parent}
{
    timer.start(10);
    connect(&timer,SIGNAL(timeout()),this,SLOT(readByte()));
    //cada vez que timer tire la señal timeout, ejecutara el metodo slot
}

QStringList SerialCommunicator::listAvailablePorts()
{
    QSerialPortInfo info;
    QStringList portList;
    for(int i{};i<info.availablePorts().size();i++){
        portList.append(info.availablePorts()[i].portName());
    }
    return portList;
}

void SerialCommunicator::setPortName(const QString name)
{
    portName = name;
    port.setPortName(name);
    port.setBaudRate(9600);
    emit portNameChanged(name);
}

QString SerialCommunicator::getPortName()
{
    return portName;
}

void SerialCommunicator::openPort()
{
    port.open(QIODevice::ReadWrite);
    if(port.isOpen()){
        qDebug() << "Puerto abierto correctamente";
    }else{
        qDebug() << "No se pudo abrir el puerto";
    }
}

void SerialCommunicator::closePort()
{
    port.close();
    qDebug() << "Puerto cerrado correctamente.";
}

void SerialCommunicator::sendByte(char data)
{
    if(port.isOpen()){

        port.write(&data);
    }
}

void SerialCommunicator::sendString(QString data)
{
    if(port.isOpen()){

        port.write(data.toLatin1());
    }
}

void SerialCommunicator::readByte()
{
    if(port.bytesAvailable()>0){
        char dato;
        port.read(&dato, 1);
        emit valueReceived(dato);
    }
}
