#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

//uniform float time;
//uniform float speed = 5.0;

out vec2 uv;
out vec3 normal;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(){
	//float dx = 0.3;
	//float offsetX = sin(time*speed) * dx;

	//float scale = 1.0/time;

	vec4 position = vec4(aPos,1.0);
	position = projectionMatrix * viewMatrix * transform * position;
	//gl_Position = vec4((aPos.x + offsetX)*scale,aPos.y*scale,aPos.z*scale,1.0);
	gl_Position = vec4(position);
	//color = aColor;
	uv = aUv;
	normal = aNormal;
}