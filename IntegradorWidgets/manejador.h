#ifndef MANEJADOR_H
#define MANEJADOR_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
class Manejador : public QObject
{
    Q_OBJECT
public:
    //PUBLIC FUNCTIONS
    Manejador();
    QSerialPort& getPort();
    QString getCurrentSignal();
    QVector<QByteArray> getSignals();
    //PUBLIC VARIABLES

    int readVariable;
private:
    //PRIVATE FUNCTIONS
    void createSignals(QByteArray message);


    //PRIVATE VARIABLES

    QSerialPort port;
    QString currentSignal;
    QVector<QByteArray> signalsReceived;
public slots:
    void readData();

signals:
    void activablesSTARTySTOP();
    void currentSignalview();
};

#endif // MANEJADOR_H
