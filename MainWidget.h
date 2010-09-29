#ifndef _MAINWIDGET_H
#define _MAINWIDGET_H

#include <QWidget>
#include "GLWidget.h"
#include <QPushButton>

class MainWidget : public QWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    MainWidget(QWidget *parent = NULL);

protected:
    void keyPressEvent(QKeyEvent *event);

    GLWidget *glwidget;
    QPushButton *play;
};

#endif  /* _MAINWIDGET_H */
