#include "manejadorinterface.h"
#include <QDebug>
ManejadorInterface::ManejadorInterface(QObject *parent)
    : QObject{parent}
{

}

QSerialPort &ManejadorInterface::getPort()
{
    return manager.getPort();
}

QString ManejadorInterface::getCurrentSignal()
{
    return manager.getCurrentSignal();
}

QString ManejadorInterface::getCurrentSignalClean()
{
    QString ret="";

    if (manager.getCurrentSignal().contains('\r')){
        ret = manager.getCurrentSignal().split('\r')[0];
    }
    return ret;
}

QVector<QByteArray> ManejadorInterface::getSignals()
{

    return manager.getSignals();
}

Manejador &ManejadorInterface::getManager()
{
    return manager;
}

void ManejadorInterface::initPort(QString name)
{
    return manager.initPort(name);
}

void ManejadorInterface::readData()
{
    manager.readData();
}

QVector<QString> ManejadorInterface::getSignalsString(){
    QVector<QString> dev;
    for (int i {}; i<manager.getSignals().size();i++){
        dev.append(manager.getSignals()[i]);
    }
    return dev;
}

void ManejadorInterface::writeText(QString text)
{
    manager.writeText(text);
}

void ManejadorInterface::setReadVariable(int val)
{
    manager.readVariable = val;
}
