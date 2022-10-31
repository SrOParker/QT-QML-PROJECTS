#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QObject>
#include <QTimer>

#include "systeminfo.h"

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
private:
    QTimer timer;
signals:
    void actualizarCPU(double datoCPU);
private slots:
    void enviarDatos();
};

#endif // THREAD_H
