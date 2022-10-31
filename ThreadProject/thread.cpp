#include "thread.h"
#include <QDebug>
Thread::Thread(){
    corriendo = true;
}

void Thread::stop()
{
    QMutexLocker locker(&mutex);
    corriendo = false;
}

void Thread::setText(const QString &str)
{

    text = str;

}

void Thread::run(){
    while(true){
        QMutexLocker locker(&mutex);
        if (!corriendo){
            corriendo = false;
            break;
        }
        qDebug()<<text;
        emit(modifyLabel(text));
    }
}
