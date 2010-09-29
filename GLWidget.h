#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include "model.h"

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(int w, int h, QWidget *parent = NULL);
    virtual ~GLWidget();

    void rotateLeft();
    void rotateRight();
    void rotateUp();
    void rotateDown();

public slots:
    void playOne();
    void playN(int n);
    void playPause();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void updatePointsAndNormals();
    void paintGL();

    Model model;

    double dx, dz, up;
    int cx, cz;

    typedef double vec[3];
    vec *v;
    vec *n;

    QTimer *timer;
};

#endif  /* _GLWIDGET_H */
