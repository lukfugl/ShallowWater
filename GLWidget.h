#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "model.h"

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(int w, int h, QWidget *parent = NULL);
    virtual ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void updatePointsAndNormals();
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    Model model;

    double dx, dz, up;
    int cx, cz;

    typedef double vec[3];
    vec *v;
    vec *n;
};

#endif  /* _GLWIDGET_H */
