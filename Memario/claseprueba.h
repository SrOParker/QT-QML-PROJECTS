#ifndef CLASEPRUEBA_H
#define CLASEPRUEBA_H

#include "qdebug.h"
#include <QObject>

class ClasePrueba : public QObject
{
    Q_OBJECT
public:
    explicit ClasePrueba(QObject *parent = nullptr);

    Q_INVOKABLE void imprimirStringPorConsola(const QString &str); //qinvocable es para poder invocar esta funcion desde otra app por ejemplo desde qml

signals:

};

#endif // CLASEPRUEBA_H
