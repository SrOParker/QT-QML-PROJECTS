#ifndef READERHANDLER_H
#define READERHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class ReaderHandler : public QObject
{
    Q_OBJECT
public:
    explicit ReaderHandler(QObject *parent = nullptr);
    Q_INVOKABLE void open(QString nombre);
    Q_INVOKABLE void close();
    Q_INVOKABLE double read();
    Q_INVOKABLE bool archiveOpened();

private:
    QFile       manejador;
    QTextStream texto;

};

#endif // READERHANDLER_H
