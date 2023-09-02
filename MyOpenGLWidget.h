#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>

class MyOpenGLWidget :
    public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
};

