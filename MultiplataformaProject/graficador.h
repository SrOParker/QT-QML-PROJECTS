#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QWidget>
#include <QPainter>
#include <QPen>
class Graficador : public QWidget
{
    Q_OBJECT
public:
    explicit Graficador(QWidget *parent = nullptr);
    void nuevoDato(double nD);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
public slots:
    void actualizarZoom(double z);
private:
    QVector<double> datos;
    double zoom;
};

#endif // GRAFICADOR_H
