#include "graficador.h"

Graficador::Graficador(QWidget *parent)
    : QWidget{parent}
{
   zoom = 0.5;
}

void Graficador::nuevoDato(double nD)
{
    datos.append(nD);
    if(datos.size() > (width() / 10)){
        datos.removeFirst();
    }
    update();
}

void Graficador::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setPen(Qt::RoundJoin);

    painter.setBrush(Qt::green);

    for (int i {}; i < datos.size() - 1; ++i){
        painter.drawLine(i*5,(height()- datos[i])*zoom, (i+1)*5, (height()- datos[i+1])*zoom);
    }
    painter.drawLine(0,0,0,height()-20);
    painter.drawLine(0,height()-20,width(),height()-20);
}

void Graficador::actualizarZoom(double z)
{
    zoom = z;
    update();
}
