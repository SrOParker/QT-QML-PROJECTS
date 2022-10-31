#ifndef THREAD_H
#define THREAD_H

#include <QMutex>
#include <QThread>
#include <QObject>
#include <QMutexLocker>

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();

    void stop();
    void setText(const QString &str);
    //QString getText();
protected:
    virtual void run() override;    // QThread interface

private:
    //volatile bool corriendo; //volatile no optimiza, evalua el estado de la variable cada vez
    volatile bool corriendo;
    QString text;
    QMutex mutex;

signals:
    void modifyLabel(const QString &str);
};

#endif // THREAD_H
