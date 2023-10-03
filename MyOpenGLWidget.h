#pragma once
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLTexture>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>

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
	void keyPressEvent(QKeyEvent *event);
signals:

public slots:
	void on_timeout();
private:
	Shape m_shape;
	QOpenGLShaderProgram shaderProgram;
	QOpenGLTexture* textureWall;
	QOpenGLTexture* textureSmile;
	QTimer timer;
};

