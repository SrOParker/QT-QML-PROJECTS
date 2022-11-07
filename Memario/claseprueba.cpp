#include "claseprueba.h"

ClasePrueba::ClasePrueba(QObject *parent)
    : QObject{parent}
{

}

void ClasePrueba::imprimirStringPorConsola(const QString &str)
{
    qDebug()<<str;
}
