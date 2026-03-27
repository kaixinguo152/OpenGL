#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

//uniform float time;
//uniform float speed = 5.0;

out vec2 uv;
out vec3 normal;
out vec3 worldPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

void main(){
    //float dx = 0.3;
    //float offsetX = sin(time*speed) * dx;

    //float scale = 1.0/time;

    vec4 transformPosition = vec4(aPos, 1.0f);

    //计算当前顶点的worldposition
    transformPosition = modelMatrix * transformPosition;

    worldPosition = transformPosition.xyz;

    gl_Position = projectionMatrix * viewMatrix * transformPosition;
    //gl_Position = vec4((aPos.x + offsetX)*scale,aPos.y*scale,aPos.z*scale,1.0);
    //color = aColor;
    uv = aUv;
    //normal = transpose(inverse(mat3(modelMatrix))) * aNormal;
    normal = normalMatrix * aNormal;
}