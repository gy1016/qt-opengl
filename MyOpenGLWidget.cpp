#include "MyOpenGLWidget.h"

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;
// 三角形
//float vertices[] = {
//	-0.5f, -0.5f, 0.0f,
//	0.5f, -0.5f, 0.0f,
//	0.0f, 0.5f, 0.0f
//};
float vertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};
float ratio = 0.5;

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
	// 不写这句话获取不到键盘事件
	setFocusPolicy(Qt::StrongFocus);
	connect(&timer, &QTimer::timeout, this, &MyOpenGLWidget::on_timeout);
	timer.start(100);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
	makeCurrent();
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	doneCurrent();
}

void MyOpenGLWidget::drawShape(Shape shape)
{
	m_shape = shape;
	update();
}

void MyOpenGLWidget::setWireFrame(bool enable)
{
	makeCurrent();
	if (enable)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	update();
	doneCurrent();
}

void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	// 创建VBO, EBO和VAO对象，并赋予ID
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	// 绑定VBO, VAO和EBO对象
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 向指定的target缓冲填充数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 告知显卡如何解析缓冲里的属性值
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 开启VAO管理的第一个属性值
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	textureWall = new QOpenGLTexture(QImage("wall.jpg").mirrored());
	textureSmile = new QOpenGLTexture(QImage("smile.jpg").mirrored());

	// 释放
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "polygon.vert");
	shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "polygon.frag");
	shaderProgram.link();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MyOpenGLWidget::paintGL()
{
	QMatrix4x4 matrix;
	unsigned int time = QTime::currentTime().msec();
	matrix.rotate(time, 0.0f, 0.0f, 1.0f);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 先使用绑定好的shader程序
	shaderProgram.bind();

	shaderProgram.setUniformValue("textureWall", 0);
	shaderProgram.setUniformValue("textureSmile", 1);
	// 要用的时候先绑定
	glBindVertexArray(VAO);
	// VBO开始绘制
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	switch (m_shape)
	{
	case MyOpenGLWidget::None:
		break;
	case MyOpenGLWidget::Rect:
		// glActiveTexture(GL_TEXTURE0);
		textureWall->bind(0);
		// glActiveTexture(GL_TEXTURE1);
		textureSmile->bind(1);
		shaderProgram.setUniformValue("modelMatrix", matrix);
		// 多级纹理相关
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;
	default:
		break;
	}
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Up:
		ratio += 0.1;
		break;
	case Qt::Key_Down:
		ratio -= 0.1;
		break;
	default:
		break;
	}
	if (ratio > 1) ratio = 1;
	if (ratio < 0) ratio = 0;
	shaderProgram.bind();
	shaderProgram.setUniformValue("ratio", ratio);
	update();
}

void MyOpenGLWidget::on_timeout()
{
	update();
}