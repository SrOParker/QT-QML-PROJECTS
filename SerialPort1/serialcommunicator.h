#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QObject>
#include <QTimer>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit SerialCommunicator(QObject *parent = nullptr);
    Q_INVOKABLE QStringList listAvailablePorts();

    Q_PROPERTY(QString portName READ getPortName WRITE setPortName NOTIFY portNameChanged);

private:
    QString     portName;
    QSerialPort     port;
    QTimer         timer;

    void setPortName(const QString name);
    QString getPortName();


signals:
    void portNameChanged(QString);
    void valueReceived(char value);

public slots:
    Q_INVOKABLE void openPort();
    Q_INVOKABLE void closePort();
    Q_INVOKABLE void sendByte(char data);
    Q_INVOKABLE void sendString(QString data);
private slots:
    void readByte();
};

#endif // SERIALCOMMUNICATOR_H
