#include "systeminfowindows.h"

SystemInfoWindows::SystemInfoWindows() :
    SystemInfo()
{

}

void SystemInfoWindows::init()
{
    cargaCpuUltimo = obtenerDatosCpu();
}

double SystemInfoWindows::cpuLoad()
{

    QVector<qulonglong> datosViejos = cargaCpuUltimo;
    QVector<qulonglong> datosNuevos = obtenerDatosCpu();
    cargaCpuUltimo = datosNuevos;

    qulonglong idleActual = datosNuevos[0] - datosViejos[0];
    qulonglong kernelActual = datosNuevos[1] - datosViejos[1];
    qulonglong userActual = datosNuevos[2] - datosViejos[2];

    qulonglong sistema = kernelActual + userActual;
    double porcentaje = (sistema - idleActual)*100.0 / sistema;
    //porcentaje de ocupacion de cpu
    return qBound(0.0, porcentaje, 100.0);
}

double SystemInfoWindows::memoryUsed()
{
    //struct de datos de memoria de windows
    MEMORYSTATUSEX estadoMemoria;

    estadoMemoria.dwLength = sizeof(MEMORYSTATUSEX);

    //asigna valor a todo el struct MEMORYSTATUSEX
    GlobalMemoryStatusEx(&estadoMemoria);

    //entero sin signo de 8 bits similar a qint64
    //memoria utilizada = memoria total - disponible
    qulonglong memoriaUtilizada = estadoMemoria.ullTotalPhys - estadoMemoria.ullAvailPhys;

    //porcentaje de memoria utilizada
    return (double) memoriaUtilizada/ (double) estadoMemoria.ullTotalPhys * 100.0;
}

QVector<qulonglong> SystemInfoWindows::obtenerDatosCpu()
{
    FILETIME idle, kernel, user;

    GetSystemTimes(&idle, &kernel, &user);

    QVector<qulonglong> datoDevuelto;
    datoDevuelto.append(convertirFileTime(idle));
    datoDevuelto.append(convertirFileTime(kernel));
    datoDevuelto.append(convertirFileTime(user));

    return datoDevuelto;

}

qlonglong SystemInfoWindows::convertirFileTime(const FILETIME &filetime) const
{
    ULARGE_INTEGER large_int;
    large_int.LowPart = filetime.dwLowDateTime;
    large_int.HighPart = filetime.dwHighDateTime;

    return large_int.QuadPart;
}













