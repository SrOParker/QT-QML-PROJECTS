#include "manejador.h"
#include <QDebug>
Manejador::Manejador()
{
    readVariable =0;
    connect(&port, SIGNAL(readyRead()), this, SLOT(readData()));
    currentSignal = "NONE";

}

QSerialPort &Manejador::getPort()
{
    return port;
}

QString Manejador::getCurrentSignal()
{
    return currentSignal;
}

QVector<QByteArray> Manejador::getSignals()
{
    return signalsReceived;
}

void Manejador::initPort(QString name)
{
    port.setPortName(name);
    port.setBaudRate(QSerialPort::Baud115200);
    if (port.open(QIODeviceBase::ReadWrite)) {
        qDebug() << ("Puerto abierto exitosamente");
    }
    else {
        qDebug() << ("Error al abrir puerto");
    }

    port.write("AT+SIGNALS=?");
}

void Manejador::writeText(QString text)
{
    port.write(text.toLatin1());
}

void Manejador::createSignals(QByteArray message)
{
    QVector<QByteArray> signalsCreated;
    signalsCreated = message.split('+');

    for (int i=0; i < signalsCreated.size();i++){
        signalsReceived.append(signalsCreated[i].split('\r')[0]);
    } signalsReceived.pop_front();
    //for(int i=0; i < signalsReceived.size();i++){
    //    qDebug()<< signalsReceived[i];
    //}
}

void Manejador::readData(){

    //ESTE SERÍA EL RESULTADO DE LLAMAR A AT+SIGNALS=? y para recibir DATOS
    if (readVariable==0){
        QByteArray message;
        while (port.bytesAvailable()) {
            message.append(port.readLine());
        }
        //qDebug() << message;
        if (message.contains("AT+RAND") || message.contains("AT+SQUARE") || message.contains("AT+SINE") || message.contains("AT+TRIANGULAR")){
            //es el modo de la señal
            createSignals(message);
        }else{
            //es un dato
            //pasar a dato y pintar

            //qDebug() << "FUERA BUCLE " + message;
            float dato=0 ;
            if (!message.contains('OK')){
                dato = message.split('=')[1].split('\r')[0].toFloat();
                //qDebug() << dato;
                emit signalDataEmited(dato);
            }


        }
    }else if (readVariable==1){//CURRENT SIGNAL
        QByteArray message;
        while (port.bytesAvailable()) {
            message.append(port.readLine());
        }
        //qDebug() << message;
        if(!message.contains('OK')){
            currentSignal = message.split('+')[1];
        }

        emit currentSignalview();
    }

}
