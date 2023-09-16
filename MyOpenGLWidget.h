#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>

class MyOpenGLWidget :
	public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
public:
	enum Shape { None, Rect, Circle, Triangle };
	explicit MyOpenGLWidget(QWidget* parent = nullptr);
	~MyOpenGLWidget();

	void drawShape(Shape shape);
	void setWireFrame(bool enable);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
signals:

public slots:
private:
	Shape m_shape;
};

