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
    static double nx[W*H];
    static double ny[W*H];
    static double nz[W*H];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    glShadeModel(GL_SMOOTH);

    int i, j, n;
    double dx = 2.0 / W, dy = 2.0 / H;
    for (j = 0, n = 0; j < H; ++j) {
        for (i = 0; i < W; ++i, ++n) {
            x[n] = i * dx - 1;
            y[n] = j * dy - 1;
            z[n] = model[n].h() - 1;
        }
    }

    double q, top, right, bottom, left, up = dx * dy;
    for (j = 0, n = 0; j < H; ++j) {
        for (i = 0; i < W; ++i, ++n) {
            if (j < H-1)
                top = dx * (z[n] - z[n+W]);
            if (i < W-1)
                right = dy * (z[n] - z[n+1]);
            if (j > 0)
                bottom = dx * (z[n-W] - z[n]);
            if (i > 0)
                left = dy * (z[n-1] - z[n]);

            if (j < H-1) {
                if (i > 0) {
                    // top->left
                    q = 1 / sqrt(left*left + top*top + up*up);
                    nx[n] += left * q;
                    ny[n] += top  * q;
                    nz[n] += up   * q;
                }
                if (i < W-1) {
                    // right->top
                    q = 1 / sqrt(right*right + top*top + up*up);
                    nx[n] += right * q;
                    ny[n] += top   * q;
                    nz[n] += up    * q;
                }
            }
            if (j > 0) {
                if (i < W-1) {
                    // bottom->right
                    q = 1 / sqrt(right*right + bottom*bottom + up*up);
                    nx[n] += right  * q;
                    ny[n] += bottom * q;
                    nz[n] += up     * q;
                }
                if (i > 0) {
                    // left->bottom
                    q = 1 / sqrt(left*left + bottom*bottom + up*up);
                    nx[n] += left   * q;
                    ny[n] += bottom * q;
                    nz[n] += up     * q;
                }
            }
            // normalize
            q = 1 / sqrt(nx[n]*nx[n] + ny[n]*ny[n] + nz[n]*nz[n]);
            nx[n] *= q;
            ny[n] *= q;
            nz[n] *= q;
        }
    }

    for (j = 0, n = 0; j < H - 1; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i < W; ++i, ++n) {
            glNormal3f(nx[n], nz[n], -ny[n]); 
            glVertex3f(x[n], z[n], -y[n]); 
            glNormal3f(nx[n+W], nz[n+W], -ny[n+W]); 
            glVertex3f(x[n+W], z[n+W], -y[n+W]); 
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
