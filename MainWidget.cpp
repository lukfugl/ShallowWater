#include "MainWidget.h"
#include "GLWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QSignalMapper>
#include <QtGui/QMouseEvent>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setSpacing(10);

    glwidget = new GLWidget(100, 100, this);
    glwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hbox->addWidget(glwidget);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setSpacing(2);
    hbox->addLayout(vbox);

    QSignalMapper *playSignalMapper = new QSignalMapper(this);

    QPushButton *step = new QPushButton("Step", this);
    vbox->addWidget(step);
    playSignalMapper->setMapping(step, 1);
    connect(step, SIGNAL(clicked()), playSignalMapper, SLOT(map()));

    QPushButton *play10 = new QPushButton("Play 10", this);
    vbox->addWidget(play10);
    playSignalMapper->setMapping(play10, 10);
    connect(play10, SIGNAL(clicked()), playSignalMapper, SLOT(map()));

    QPushButton *play100 = new QPushButton("Play 100", this);
    vbox->addWidget(play100);
    playSignalMapper->setMapping(play100, 100);
    connect(play100, SIGNAL(clicked()), playSignalMapper, SLOT(map()));

    connect(playSignalMapper, SIGNAL(mapped(int)), glwidget, SLOT(playN(int)));

    play = new QPushButton("Play/Pause", this);
    vbox->addWidget(play);
    connect(play, SIGNAL(clicked()), glwidget, SLOT(playPause()));

    vbox->addStretch(1);

    QPushButton *exit = new QPushButton("Exit", this);
    vbox->addWidget(exit);
    connect(exit, SIGNAL(clicked()), qApp, SLOT(quit()));

    setLayout(hbox);
}

void MainWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_H:
        glwidget->rotateLeft();
        break;
    case Qt::Key_L:
        glwidget->rotateRight();
        break;
    case Qt::Key_K:
        glwidget->rotateUp();
        break;
    case Qt::Key_J:
        glwidget->rotateDown();
        break;
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_I:
        play->click();
        break;
    default:
        event->ignore();
        break;
    }
}
