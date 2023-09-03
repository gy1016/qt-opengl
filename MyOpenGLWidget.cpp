#include "MyOpenGLWidget.h"

unsigned int VBO, VAO;
unsigned int shaderProgram;
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};
const char* vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPox;\n void main()\n{\ngl_Position = vec4(aPox, 1.0);\n}\0";
const char* fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n}\0";

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {

}

void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	
	// ����VBO��VAO���󣬲�����ID
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ��VBO��VAO����
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// ��ָ����target�����������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��֪�Կ���ν��������������ֵ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ����VAO����ĵ�һ������ֵ
	glEnableVertexAttribArray(0);

	// �ͷ�
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	int success;
	char infoLog[512];
	// ������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
	}

	// Ƭ����ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
	}

	// ������ɫ��
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
	}

	// ������Ͳ����ˣ�ɾ��
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
	
	// ��ʹ�ð󶨺õ�shader����
	glUseProgram(shaderProgram);
	// Ҫ�õ�ʱ���Ȱ�
	glBindVertexArray(VAO);
	// ��ʼ����
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
