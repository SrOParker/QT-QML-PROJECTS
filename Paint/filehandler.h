#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);
    Q_INVOKABLE void escribir(int x, int y);
    Q_INVOKABLE void abrirArchivo(QString nombre);
    Q_INVOKABLE void cerrarArchivo();
    Q_INVOKABLE bool archiveOpened();
private:
    QFile       manejador;
    QTextStream texto;
signals:

};

#endif // FILEHANDLER_H
