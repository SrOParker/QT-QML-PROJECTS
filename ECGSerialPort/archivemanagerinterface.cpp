#include "archivemanagerinterface.h"

ArchiveManagerInterface::ArchiveManagerInterface(QObject *parent)
    : QObject{parent}
{

}

void ArchiveManagerInterface::readFromTXT(const QString &file)
{
    man.readFromTXT(file);
}

double ArchiveManagerInterface::getOneInData(int position)
{
    return man.getOneInData(position);
}

QVector<double> ArchiveManagerInterface::getAllData()
{
    return man.getAllData();
}

void ArchiveManagerInterface::startTimer(int n)
{
    man.startTimer(n);
}

void ArchiveManagerInterface::startSerialCom(const QString &file, const QString &port, float timerVel, QSerialPort::BaudRate baud)
{
    man.startSerialCom(file, port,timerVel, baud);
}

void ArchiveManagerInterface::stopSerialCom()
{
    man.stopSerialCom();
}

void ArchiveManagerInterface::resetPositionRec()
{
    man.resetPositionRec();
}
