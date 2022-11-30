#ifndef ARCHIVEMANAGERRECEIVER_H
#define ARCHIVEMANAGERRECEIVER_H

#include <QObject>
#include <QSerialPort>
#include <QVariant>
class ArchiveManagerReceiver : public QObject
{
    Q_OBJECT
public:
    explicit ArchiveManagerReceiver(QObject *parent = nullptr);

    float getDataAt(int p);

protected:
    QSerialPort port;
    QVariantList buffer;

protected slots:
    void readData();
public slots:
    void errorPort();
    void startSerialCom(const QString &port, QSerialPort::BaudRate baud);

signals:
    void started();
    void stopped();
    void portError();
    void dataReceived(QVariantList data);
private:
    QVector<float> data;
};

#endif // ARCHIVEMANAGERRECEIVER_H
