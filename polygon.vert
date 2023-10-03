#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCord;

out vec3 outColor;
out vec2 texCord;

uniform mat4 modelMatrix;

void main() {
	gl_Position = modelMatrix * vec4(aPos, 1.0f);
	outColor = aColor;
	texCord = aTexCord;
}
