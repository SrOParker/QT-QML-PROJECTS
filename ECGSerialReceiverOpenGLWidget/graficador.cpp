#include "graficador.h"
#include <QDebug>
Graficador::Graficador(QWidget *parent) : QOpenGLWidget(parent)
{
    background = QColor("#06AD90");
    signalColor = QColor("#06CDAA");
    graphicZoom = 200;
}

void Graficador::addValueToSignal(float newData)
{
    while (signal.size()>width()){
        signal.removeFirst();
    }

    signal.append(newData);

    qDebug()<< "DATO: " << newData;

    update(); //con esta funcion tambien se llama a paintevent que a su vez llama a paintGL
    //update actualiza la pantalla por lo tanto repinta
}

void Graficador::initializeGL()
{
    // pertenece a la clase OpenGLFunctions_1_1 incluida
    initializeOpenGLFunctions();

    // rgb alpha  ------- glClearColor(rgba) -> color con el que borramos
    glClearColor(background.redF(),background.greenF(),background.blueF(),background.alphaF());
}

void Graficador::resizeGL(int w, int h)
{
    glViewport(0, 0,w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, w* 1.0f, 0.0f, h*1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graficador::paintGL()
{
    /*//EJEMPLO PAINT TRIANGLE & PAINT LINE
    // BORRA utilizando el buffer de color
    glClear(GL_COLOR_BUFFER_BIT);
    glScalef(1.0,1.0,1.0);
    //glRotatef(45.0,0.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); //color rojo para el triángulo
        glVertex3f(0.0, 0.0,0.0);

        glColor3f(0.0f, 1.0f, 0.0f); //color rojo para el triángulo
        glVertex3f(100.0, 200.0,0.0);

        glColor3f(0.0f, 0.0f, 1.0f); //color rojo para el triángulo
        glVertex3f(300.0, 0.0,0.0);
    glEnd();
    glPopMatrix();

    glFlush();
    //for(int i{}; i < 300;i+=10){
    //    glVertex3f(i * 1.0f, i *1.0f, 0.0f);
    //    glVertex3f((i+10) * 1.0f, (i+10) *1.0f, 0.0f);
    //}

    */
    glPushMatrix();
    glScalef(1.0, graphicZoom*1.0, 1.0);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

        glColor3f(signalColor.redF(), signalColor.greenF(), signalColor.blueF());

        for(int i{}; i < signal.size()-1 ;i++){
            glVertex3f(i*1.0f, signal[i] , 0.0f);
            glVertex3f((i+1) * 1.0f, signal[i+1] , 0.0f );
        }

    glEnd();

    glPopMatrix();

    glFlush();
}

void Graficador::wheelEvent(QWheelEvent *event)
{
    if (!event->angleDelta().isNull()){
        if (event->angleDelta().y() > 0){
            //INCREMENTO DE ZOOM
            if (graphicZoom < 450){
                graphicZoom +=10;
            }
        }else{
            //DECREMENTO DE ZOOM
            if (graphicZoom > 20){
                graphicZoom -=10;
            }
        }
        update();
    }

}
