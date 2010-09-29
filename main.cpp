#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>
#include "GLWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GLWidget window(100, 100);
    window.resize(800,600);
    window.show();

    return app.exec();
}
