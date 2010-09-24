#include <QtGui/QMouseEvent>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "GLWidget.h"

double rotX = 0;
double rotY = 0;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent),
    model(10, 10, "a.in") {
    setMouseTracking(true);
    for (int i = 0; i < 10; ++i)
        model.step();
}

void GLWidget::initializeGL() {

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    // lighting
    static float ambient[]        = { 0.1, 0.1, 0.1, 1.0 };
    static float diffuse[]        = { 1.0, 1.0, 1.0, 1.0 };
    static float position[]       = { 0.0, 0.0, -150.0, 0.0 };
    static float lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    static float lmodel_twoside[] = { GL_TRUE };
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
    glEnable(GL_LIGHT0);

    // material
    static float front_mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    static float back_mat_diffuse[]  = { 0.0, 0.0, 0.4, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
    glEnable(GL_AUTO_NORMAL);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -0.5, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glShadeModel(GL_SMOOTH);

    int i, j, n = 0;
    for (j = 0; j < 10 - 1; ++j, ++n) {
        for (i = 0; i < 10 - 1; ++i, ++n) {
            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(i * 0.2 - 1, model[n].h() - 1, j * 0.2 - 1); 
            glVertex3f(i * 0.2 - 1, model[n + 10].h() - 1, (j + 1) * 0.2 - 1); 
            glVertex3f((i + 1) * 0.2 - 1, model[n + 1].h() - 1, j * 0.2 - 1); 
            glVertex3f((i + 1) * 0.2 - 1, model[n + 11].h() - 1, (j + 1) * 0.2 - 1);
            glEnd();
        }
    }

    glPopMatrix();
    glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {

}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {

}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Left:
        rotY -= 10;
        repaint();
        break;
    case Qt::Key_Right:
        rotY += 10;
        repaint();
        break;
    case Qt::Key_Up:
        rotX -= 10;
        repaint();
        break;
    case Qt::Key_Down:
        rotX += 10;
        repaint();
        break;
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}
