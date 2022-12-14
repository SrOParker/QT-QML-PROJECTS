#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>

#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QtOpenGL/QOpenGLFunctions_1_1>
class Canvas : public QOpenGLWidget, protected QOpenGLFunctions_1_1
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);
    QColor background;
    Q_INVOKABLE void passDataAndPaint(float valueX, float valueY);
    float x,y, xant, yant;
    QVector<float> signal;
    // QOpenGLWidget interface
protected:
    Q_INVOKABLE void initializeGL() override;
    Q_INVOKABLE void resizeGL(int w, int h) override;
    Q_INVOKABLE void paintGL() override;
};

#endif // CANVAS_H
