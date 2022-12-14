#include "archivemanagerinterface.h"

ArchiveManagerInterface::ArchiveManagerInterface(QObject *parent)
    : ArchiveManager{parent}
{

}

void ArchiveManagerInterface::readFromTXT(const QString &file)
{
    man.readFromTXT(file);
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
