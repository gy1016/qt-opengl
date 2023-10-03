#version 330 core
in vec3 outColor;
in vec2 texCord;

uniform sampler2D textureWall;
uniform sampler2D textureSmile;

out vec4 FragColor;

void main(){
	FragColor = mix(texture(textureWall, texCord), texture(textureSmile, texCord), 0.5);
	// FragColor = vec4(1.0);
}