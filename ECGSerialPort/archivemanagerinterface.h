#ifndef ARCHIVEMANAGERINTERFACE_H
#define ARCHIVEMANAGERINTERFACE_H

#include <QObject>
#include "archivemanager.h"
class ArchiveManagerInterface : public ArchiveManager
{
    Q_OBJECT
public:
    explicit ArchiveManagerInterface(QObject *parent = nullptr);
    Q_INVOKABLE void readFromTXT(const QString &file);


    Q_INVOKABLE void startSerialCom(const QString &file, const QString &port, float timerVel, QSerialPort::BaudRate baud);
    Q_INVOKABLE void stopSerialCom();

    Q_INVOKABLE void resetPositionRec();
private:
    ArchiveManager man;
};

#endif // ARCHIVEMANAGERINTERFACE_H
