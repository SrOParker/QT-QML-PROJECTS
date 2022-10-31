#include "thread.h"

Thread::Thread()
{
    SystemInfo::instancia().init();

    connect(&timer, SIGNAL(timeout()), this, SLOT(enviarDatos()));
    timer.start(100);
}

void Thread::enviarDatos()
{
    emit actualizarCPU(SystemInfo::instancia().cpuLoad());
}
