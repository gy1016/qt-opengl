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
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};
const char* vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPox;\n void main()\n{\ngl_Position = vec4(aPox, 1.0);\n}\0";
const char* fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n}\0";

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {

}

MyOpenGLWidget::~MyOpenGLWidget()
{
	makeCurrent();
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 开启VAO管理的第一个属性值
	glEnableVertexAttribArray(0);

	// 释放
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int success;
	char infoLog[512];
	// 顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
	}

	// 片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
	}

	// 编译着色器
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
	}

	// 编译完就不用了，删掉
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MyOpenGLWidget::paintGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 先使用绑定好的shader程序
	glUseProgram(shaderProgram);
	// 要用的时候先绑定
	glBindVertexArray(VAO);
	// VBO开始绘制
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	switch (m_shape)
	{
	case MyOpenGLWidget::None:
		break;
	case MyOpenGLWidget::Rect:
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		break;
	default:
		break;
	}
}
