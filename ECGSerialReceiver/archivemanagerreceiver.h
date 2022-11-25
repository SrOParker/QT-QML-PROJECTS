#ifndef ARCHIVEMANAGERRECEIVER_H
#define ARCHIVEMANAGERRECEIVER_H

#include <QObject>
#include <QTimer>
#include <QSerialPort>
class ArchiveManagerReceiver : public QObject
{
    Q_OBJECT
public:
    explicit ArchiveManagerReceiver(QObject *parent = nullptr);

    void startSerialCom(const QString &port, QSerialPort::BaudRate baud);
    void stopSerialCom();

    void startTimer(int n );
private:
    QSerialPort port;
    QTimer timer;
private slots:
    void recibir();
    void errorPort();
signals:
    void started();
    void portError();
};

#endif // ARCHIVEMANAGERRECEIVER_H
