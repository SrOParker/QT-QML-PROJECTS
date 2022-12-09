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

void Manejador::createSignals(QByteArray message)
{
    QVector<QByteArray> signalsCreated;
    signalsCreated = message.split('+');

    for (int i=0; i < signalsCreated.size();i++){
        signalsReceived.append(signalsCreated[i].split('\r')[0]);
    } signalsReceived.pop_front();

}

void Manejador::readData(){

    //ESTE SERÍA EL RESULTADO DE LLAMAR A AT+SIGNALS=? y para recibir DATOS
    if (readVariable==0){
        QByteArray message;
        while (port.bytesAvailable()) {
            message.append(port.readLine());
        }
        qDebug() << message;
        if (message.contains("AT+RAND") || message.contains("AT+SQUARE") || message.contains("AT+SINE") || message.contains("AT+TRIANGULAR")){
            //es el modo de la señal
            createSignals(message);
        }else{
            //es un dato
            //pasar a dato y pintar
        }
    }else if (readVariable==1){//CURRENT SIGNAL
        QByteArray message;
        while (port.bytesAvailable()) {
            message.append(port.readLine());
        }
        qDebug() << message;
        currentSignal = message.split('+')[1];
        emit currentSignalview();
    }

}
