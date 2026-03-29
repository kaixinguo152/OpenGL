#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;

uniform float width;
uniform float height;

void main()
{
	FragColor = vec4(vec3(1.0f),1.0f);
}