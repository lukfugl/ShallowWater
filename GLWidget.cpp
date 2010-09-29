#include <QtGui/QMouseEvent>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "GLWidget.h"

double rotX = 20;
double rotY = 20;

GLWidget::GLWidget(int w, int h, QWidget *parent) : QGLWidget(parent),
    model(w, h), cx(w), cz(h) {
    dx = 2.0 / cx;
    dz = 2.0 / cz;
    up = dx * dz;
    v = new vec[cx * cz];
    n = new vec[cx * cz];
    updatePointsAndNormals();
    setMouseTracking(true);
}

GLWidget::~GLWidget() {
    delete[] v;
    delete[] n;
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

void GLWidget::updatePointsAndNormals() {
    int i, j, k;
    double q, top, right, bottom, left;

    for (j = 0, k = 0; j < cz; ++j) {
        for (i = 0; i < cx; ++i, ++k) {
            v[k][0] = i * dx - 1;
            v[k][1] = model[k].h() - 1;
            v[k][2] = j * dz - 1;
        }
    }

    for (j = 0, k = 0; j < cz; ++j) {
        for (i = 0; i < cx; ++i, ++k) {
            if (j < cz-1)
                top = dx * (v[k][1] - v[k+cx][1]);
            if (i < cx-1)
                right = dz * (v[k][1] - v[k+1][1]);
            if (j > 0)
                bottom = dx * (v[k-cx][1] - v[k][1]);
            if (i > 0)
                left = dz * (v[k-1][1] - v[k][1]);

            if (j < cz-1) {
                if (i > 0) {
                    // top->left
                    q = 1 / sqrt(left*left + top*top + up*up);
                    n[k][0] += left * q;
                    n[k][1] += up   * q;
                    n[k][2] += top  * q;
                }
                if (i < cx-1) {
                    // right->top
                    q = 1 / sqrt(right*right + top*top + up*up);
                    n[k][0] += right * q;
                    n[k][1] += up    * q;
                    n[k][2] += top   * q;
                }
            }
            if (j > 0) {
                if (i < cx-1) {
                    // bottom->right
                    q = 1 / sqrt(right*right + bottom*bottom + up*up);
                    n[k][0] += right  * q;
                    n[k][1] += up     * q;
                    n[k][2] += bottom * q;
                }
                if (i > 0) {
                    // left->bottom
                    q = 1 / sqrt(left*left + bottom*bottom + up*up);
                    n[k][0] += left   * q;
                    n[k][1] += up     * q;
                    n[k][2] += bottom * q;
                }
            }
            // normalize
            q = 1 / sqrt(n[k][0]*n[k][0] + n[k][1]*n[k][1] + n[k][2]*n[k][2]);
            n[k][0] *= q;
            n[k][1] *= q;
            n[k][2] *= q;
        }
    }
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);

    glShadeModel(GL_SMOOTH);

    int i, j, k;
    for (j = 0, k = 0; j < cz - 1; ++j) {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i < cx; ++i, ++k) {
            glNormal3dv(n[k+cx]);
            glVertex3dv(v[k+cx]);
            glNormal3dv(n[k]);
            glVertex3dv(v[k]);
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
        updatePointsAndNormals();
        repaint();
        break;
    default:
        event->ignore();
        break;
    }
}
