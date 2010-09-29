#include <QtGui/QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWidget window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}
