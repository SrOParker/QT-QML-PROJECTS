#include "readerhandler.h"

ReaderHandler::ReaderHandler(QObject *parent)
    : QObject{parent}
{

}

void ReaderHandler::open(QString nombre)
{
    manejador.setFileName(nombre);
    manejador.open(QFile::ReadOnly | QFile::Text);
    texto.setDevice(&manejador);
}

void ReaderHandler::close()
{
    manejador.close();

}

double ReaderHandler::read()
{
    if(!texto.atEnd()){
        QString line = texto.readLine();
        double y = line.toDouble();
        return y;
    }else{
        close();
    }
    return 0;
}

bool ReaderHandler::archiveOpened()
{
    return manejador.isOpen();
}
