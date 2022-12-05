#include "graphics.h"
#include <QDebug>
Graphics::Graphics(QWidget *parent) : QOpenGLWidget(parent)
{
    background = QColor("#06AD90");
    gZOOM = 1 ;
    drag=xdrag=ydrag = false;
    grad=gradY = 0;
    xmouse=ymouse=0;
    xeje=yeje=zeje=0;
    xmove=ymove=zmove=0;
    xwheeldrag=ywheeldrag=false;
    graphicZoom = 1;
    wheelPressed = false;
    scaleTrue = false;
}

void Graphics::initializeGL()
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

void Graphics::resizeGL(int w, int h)
{
    glViewport(0, 0,w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, w* 1.0f, 0.0f, h*1.0f, -800.0f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(400,300,0);

    glRotated(90,1,0,0);
    //glRotated(45,0,0,1);

}

void Graphics::paintGL()
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);
    gZOOM = 30;
    glScalef(1.0 *gZOOM,1.0*gZOOM,1.0*gZOOM);

    if(xdrag){
        glRotated(grad,xeje,yeje,zeje);
    }
    if(ydrag){
        glRotated(gradY,xejeY,yejeY,zejeY);
    }

    if(xwheeldrag){
        glTranslatef(xmove*0.1,0,0);
    }
    if (ywheeldrag){
        glTranslatef(0,0,zmove*0.1);
    }

    if (scaleTrue){
        glScalef(graphicZoom,graphicZoom,graphicZoom);
    }


    //CARA CUADRADA ABAJO
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3d(-4,0,-4);
    glColor3f(1,1,0);
    glVertex3d(-4,0,4);
    glColor3f(0,0,1);
    glVertex3d(4,0,4);
    glColor3f(0,1,0);
    glVertex3d(4,0,-4);
    glEnd();

    //CARA 1 - BLANCO AMARILLO
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex3d(0,4,0);
    glColor3f(1,1,0);
    glVertex3d(-4,0,-4);
    glVertex3d(4,0,-4);
    glEnd();
    //CARA 2 - BLANCO ROJO
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex3d(0,4,0);
    glColor3f(1,0,0);
    glVertex3d(4,0,-4);
    glVertex3d(4,0,4);
    glEnd();
    //CARA 3 - BLANCO Y VERDE
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex3d(0,4,0);
    glColor3f(0,1,0);
    glVertex3d(-4,0,4);
    glVertex3d(-4,0,-4);
    glEnd();
    //CARA 4 - BLANCO Y AZUL
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex3d(0,4,0);
    glColor3f(0,0,1);
    glVertex3d(4,0,4);
    glVertex3d(-4,0,4);
    glEnd();


    glPopMatrix();
    glFlush();

}

void Graphics::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        drag = true;
    }

    if (event->button() == Qt::MiddleButton){
        wheelPressed = true;
    }
    xmouse = event->pos().x();
    ymouse = event->pos().y();
}

void Graphics::mouseReleaseEvent(QMouseEvent *event)
{
    drag = false;
    wheelPressed =false;
    qDebug()<<"release";
}

void Graphics::mouseMoveEvent(QMouseEvent *event)
{
    //rotate left click and drag
    xeje=yeje=zeje=xejeY=yejeY=zejeY=0;
    xdrag=false;
    ydrag=false;
    if(drag == true){
        if(event->pos().x() > xmouse){
            grad-=1;
            zeje=1;
            xmouse = event->pos().x();
            xdrag=true;
        }else{
            grad+=1;
            zeje=1;
            xmouse = event->pos().x();
            xdrag=true;
        }
        if(event->pos().y()>ymouse){
            gradY+=1;
            xejeY=1;
            ymouse = event->pos().y();
            ydrag=true;
        }else{
            gradY-=1;
            xejeY=1;
            ymouse = event->pos().y();
            ydrag=true;
        }
        update();
    }

    //xmove=ymove=zmove=0;
    //translate click wheel and drag
    xwheeldrag=ywheeldrag=false;
    if(wheelPressed){
        if(event->pos().x()>xmouse){
            xmove += 1;
            xmouse = event->pos().x();
            xwheeldrag = true;
        }else{
            xmove -= 1;
            xmouse = event->pos().x();
            xwheeldrag = true;
        }

        if(event->pos().y()>ymouse){
            zmove += 1;
            ymouse = event->pos().y();
            ywheeldrag = true;
        }else{
            zmove -= 1;
            ymouse = event->pos().y();
            ywheeldrag = true;
        }
        update();
    }
}

void Graphics::wheelEvent(QWheelEvent *event)
{
    scaleTrue = false;
    if (!event->angleDelta().isNull()){
        if (event->angleDelta().y() > 0){
            //INCREMENTO DE ZOOM
            graphicZoom +=0.1;
            scaleTrue = true;

        }else{
            //DECREMENTO DE ZOOM
            graphicZoom -=0.1;
            scaleTrue = true;

        }
        update();
    }

}




















