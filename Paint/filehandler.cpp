#include "filehandler.h"

FileHandler::FileHandler(QObject *parent): QObject{parent}{

}

void FileHandler::escribir(int x, int y)
{

    texto << "X:" << x << " Y: " << y << Qt::endl;

}

void FileHandler::abrirArchivo(QString nombre)
{

    manejador.setFileName(nombre);
    manejador.open(QFile::WriteOnly | QFile::Text);
    texto.setDevice(&manejador);

}

void FileHandler::cerrarArchivo()
{
    manejador.close();

}

bool FileHandler::archiveOpened()
{
    return manejador.isOpen();
}
