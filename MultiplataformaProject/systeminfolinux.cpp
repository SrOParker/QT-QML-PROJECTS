#include "systeminfolinux.h"

SystemInfoLinux::SystemInfoLinux() : SystemInfo(){

}

void SystemInfoLinux::init()
{
    cargaCpuUltimo = obtenerDatosCpu();
}

double SystemInfoLinux::cpuLoad()
{
    QVector<qulonglong> datosViejos = cargaCpuUltimo;
    QVector<qulonglong> datosNuevos = obtenerDatosCpu();
    cargaCpuUltimo = datosNuevos;

    qulonglong userActual = datosNuevos[0] - datosViejos[0];
    qulonglong userNiceActual = datosNuevos[1] - datosViejos[1];
    qulonglong systemActual = datosNuevos[2] - datosViejos[2];
    qulonglong idleActual = datosNuevos[3] - datosViejos[3];

    qulonglong totalUsado = userNiceActual + userActual + systemActual;
    qulonglong total = totalUsado + idleActual;

    double porcentaje = ((double)totalUsado*100.0) / (double)total;
    //porcentaje de ocupacion de cpu
    return qBound(0.0, porcentaje, 100.0);
}

double SystemInfoLinux::memoryUsed()
{
    return 0.0; // not implemented
}

QVector<qulonglong> SystemInfoLinux::obtenerDatosCpu()
{
    QFile file("/pro/stat");
    file.open(QIODevice::ReadOnly);
    QByteArray primeraLinea = file.readLine();
    file.close();

    qulonglong user, userNice, system, idle;

    QTextStream texto(primeraLinea);

    QString nameCPU;
    texto >> nameCPU;

    texto >> user;
    texto >> userNice;
    texto >> system;
    texto >> idle;

    QVector<qulonglong> datosDevueltos;
    datosDevueltos.append(user);
    datosDevueltos.append(userNice);
    datosDevueltos.append(system);
    datosDevueltos.append(idle);

    return datosDevueltos;
}













