#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent)
{
    background = QColor("#06AD90");
}

void Canvas::passDataAndPaint(float valueX, float valueY)
{
    signal.append(valueY);
    x = valueX;
    y = valueY;
    //paintGL();
    update();
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(background.redF(),background.greenF(),background.blueF(),background.alphaF());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glMatrixMode(GL_MODELVIEW);
    glTranslated(0,0,-10);
    glRotated(50,1,1,0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

}

void Canvas::resizeGL(int w, int h)
{
    glViewport(0, 0,w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, w* 1.0f, -200.0f, 200.0f, -800.0f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glRotated(90,1,0,0);
}

void Canvas::paintGL()
{
    if (xant!=0 && yant!=0){
        glPushMatrix();

        glClear(GL_COLOR_BUFFER_BIT);


        //PAINTING
        glBegin(GL_LINES);
        for(int i =0; i < signal.size()-1;i++){
            qDebug()<< signal[i];
            glVertex2f(i,signal[i]);
            glVertex2f(i+1,signal[i+1]);
        }
        //glColor3f(1,1,1);
        //glVertex3f(xant,0,yant);
        //glVertex3f(x,0,y);
        glEnd();

        glPopMatrix();
        glFlush();
    }
    xant = x;
    yant = y;
}
