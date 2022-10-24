#ifndef DIACALENDARIO_H
#define DIACALENDARIO_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QMouseEvent>

class DiaCalendario : public QWidget
{
    Q_OBJECT
public:
    explicit DiaCalendario(QWidget *parent = nullptr);
    int getFecha();
    void setFecha(int date);
    void resize(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void agregarEvento(QString e);

    int cantidadEventosDia();
    QString getEvento(int indice);
private:
    QFrame recuadro;
    QLabel fecha;
    QLabel indicadorEventos;

    QVector<QString> eventos;
signals:
    void diaClickeado(int f);
    void diaHovered(const QVector<QString> &evs, int f);
};

#endif // DIACALENDARIO_H
