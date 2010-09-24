#include <QtGui/QMouseEvent>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "GLWidget.h"

#define W 100
#define H 100

double rotX = 20;
double rotY = 20;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent),
    model(W, H) {
    setMouseTracking(true);
}

void GLWidget::initializeGL() {
    static float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    static float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    static float position[] = { 0.0, 0.0, -150.0, 0.0 };
    static float front_mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    static float back_mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
    static float lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    static float lmodel_twoside[] = { GL_TRUE };

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    static double x[W*H];
    static double y[W*H];
    static double z[W*H];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glShadeModel(GL_SMOOTH);

    int i, j, n;
    for (j = 0, n = 0; j < H; ++j) {
        for (i = 0; i < W; ++i, ++n) {
            x[n] = i * 2.0 / W - 1;
            y[n] = j * 2.0 / H - 1;
            z[n] = model[n].h() - 1;
        }
    }

    for (j = 0, n = 0; j < H - 1; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i < W; ++i, ++n) {
            glVertex3f(x[n], z[n], y[n]); 
            glVertex3f(x[n+W], z[n+W], y[n+W]); 
        }
        glEnd();
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
    case Qt::Key_Space:
        model.step();
        repaint();
        break;
    default:
        event->ignore();
        break;
    }
}
