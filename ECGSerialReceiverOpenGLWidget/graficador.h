#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <QOpenGLWidget>
#include <QObject>
#include <QWheelEvent>
#include <QEvent>
#include <QOpenGLFunctions_1_1>   //Esta funciona seguro
//#include <QOpenGLFunctions_3_0>     //Probando

class Graficador : public QOpenGLWidget, protected QOpenGLFunctions_1_1
{
    Q_OBJECT
public:
    Graficador(QWidget *parent = 0);

    void addValueToSignal(float newData);

private:
    QColor signalColor;
    QColor background;
    QVector<float> signal;
    int graphicZoom;

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAFICADOR_H
