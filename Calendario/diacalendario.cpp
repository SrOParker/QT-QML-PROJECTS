#include "diacalendario.h"

DiaCalendario::DiaCalendario(QWidget *parent)
    : QWidget{parent}
{
    recuadro.setFrameStyle(QFrame::Box|QFrame::Sunken);
    recuadro.setStyleSheet("QFrame { background:white; border:1px solid black; border-radius:10px;}");

    recuadro.setParent(this);

    fecha.setParent(&recuadro);

    indicadorEventos.setParent(&recuadro);
    indicadorEventos.setStyleSheet("QLabel { background:blue; }");

    setMouseTracking(true);
}

int DiaCalendario::getFecha()
{
    return fecha.text().toInt();
}

void DiaCalendario::setFecha(int date)
{
    fecha.setNum(date);
}

void DiaCalendario::resize(int w, int h)
{
    QWidget::resize(w,h);
    recuadro.resize((int)(w*0.9), (int)(h*0.9));
    recuadro.move((int)(w*0.05), (int)(h*0.05));

    fecha.move((int)(w*0.05), (int)(h*0.05));

    indicadorEventos.resize((int)(w*0.05), (int)(h*0.05));
    indicadorEventos.move((int)(w*0.8), (int)(h*0.05));
    ;}

void DiaCalendario::mouseMoveEvent(QMouseEvent *e)
{
    emit diaHovered(eventos, fecha.text().toInt());
}

void DiaCalendario::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug()<<fecha.text();
    emit diaClickeado(fecha.text().toInt());
}

void DiaCalendario::agregarEvento(QString e)
{
    eventos.append(e);
    indicadorEventos.setStyleSheet("QLabel { background:red; }");
}

int DiaCalendario::cantidadEventosDia()
{
    return eventos.size();
}

QString DiaCalendario::getEvento(int indice)
{
    return eventos[indice];
}
