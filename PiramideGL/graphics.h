#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLFunctions_1_1>
#include <QMouseEvent>
#include <QEvent>
class Graphics : public QOpenGLWidget, protected QOpenGLFunctions_1_1
{
    Q_OBJECT
public:
    Graphics(QWidget *parent = 0);

private:
    QColor background;
    int gZOOM;

    bool drag, xdrag, ydrag;
    float grad, gradY;
    int xeje, yeje, zeje;
    int xejeY, yejeY, zejeY;

    bool wheelPressed;
    int xmove, ymove, zmove;
    bool xwheeldrag, ywheeldrag;

    float xmouse, ymouse;
    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAPHICS_H
