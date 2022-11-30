#include "archivemanager.h"

ArchiveManager::ArchiveManager(QObject *parent)
    : QObject{parent}
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendValue()));
    position = 0;
}

void ArchiveManager::readFromTXT(const QString &file)
{
    QFile archivo(file);
    QString line;
    if(archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        //Leemos el texto entero
        line = archivo.readLine();
        while (line != ""){
            addToData(line.toDouble(), line);

            line = archivo.readLine();
        }
        archivo.close();
    }
}

double ArchiveManager::getOneInData(int position)
{
    double ret = 0;
    if (position< data.size() && position >= 0){
        ret = data[position];
    }
    return ret;
}

QString ArchiveManager::getOneInDataS(int position)
{
    QString ret = "";
    if (position< data.size() && position >= 0){
        ret = dataString[position];
    }
    return ret;
}

QVector<double> ArchiveManager::getAllData()
{
    return data;
}

void ArchiveManager::addToData(double d, QString str)
{
    data.append(d);
    dataString.append(str);
}

void ArchiveManager::startTimer(int n)
{
    timer.start(n);
}

void ArchiveManager::startSerialCom(const QString &fileSignal, const QString &portn, float timerVel, QSerialPort::BaudRate baud)
{
    timer.start(1000.0 / timerVel);

    port.setBaudRate(baud);
    port.setStopBits(QSerialPort::TwoStop);
    port.setParity(QSerialPort::NoParity);
    port.setPortName(portn);
    port.open(QIODevice::WriteOnly);

    if (port.isOpen()){
        emit started();
    }else{
        emit portError();
    }

}

void ArchiveManager::stopSerialCom()
{
    port.errorString();
    port.close();
    resetPositionRec();
}

void ArchiveManager::resetPositionRec()
{
    position = 0;
}

void ArchiveManager::sendValue()
{
    double d = 0;
    if (position < 4988){
        d = getOneInData(position);
        //qDebug() << d;

        if (port.isOpen()){
            port.write(QByteArray::number(d));

            //port.write((char*)&d, sizeof(d));
        }else{
            stopSerialCom();
            emit portError();
        }

    }else{
        stopSerialCom();

    }
    position++;

}
