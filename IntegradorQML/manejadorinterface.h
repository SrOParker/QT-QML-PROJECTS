#ifndef MANEJADORINTERFACE_H
#define MANEJADORINTERFACE_H

#include <QObject>
#include "manejador.h"
class ManejadorInterface : public QObject
{
    Q_OBJECT
public:
    //PUBLIC FUNCTIONS
    explicit ManejadorInterface(QObject *parent = nullptr);

    Q_INVOKABLE QSerialPort& getPort();
    Q_INVOKABLE QString getCurrentSignal();
    Q_INVOKABLE QString getCurrentSignalClean();
    Q_INVOKABLE QVector<QByteArray> getSignals();
    Q_INVOKABLE Manejador& getManager();
    Q_INVOKABLE void initPort(QString name);
    //PUBLIC VARIABLES

    int readVariable;
    Q_INVOKABLE QVector<QString> getSignalsString();
    Q_INVOKABLE void writeText(QString text);
    Q_INVOKABLE void setReadVariable(int val);
private:
    Manejador manager;
public slots:
    Q_INVOKABLE void readData();
private slots:
    void intermedioSignal(float dato);
signals:
    void signalDataEmited(float dato);


};

#endif // MANEJADORINTERFACE_H
