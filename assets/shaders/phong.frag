#version 330 core
out vec4 FragColor;

//in vec3 color;
in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform float width;
uniform float height;

uniform sampler2D sampler;//diffuse贴图采样器
uniform sampler2D specularMaskSampler;//specularMask贴图采样器

//光源参数
//uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform float k2;
uniform float k1;
uniform float kc;
uniform vec3 lightColor;

uniform vec3 ambientColor; 

uniform vec3 cameraPosition;

uniform float specularIntensity;
uniform float shiness;

void main()
{
	//计算光照的通用数据
    vec3 objectColor = texture(sampler,uv).xyz;
	vec3 normalN = normalize(normal);
	//vec3 lightDirN = normalize(lightDirection);
	vec3 lightDirN = normalize(lightPosition - worldPosition);
	vec3 viewDir = normalize(worldPosition - cameraPosition);

	//计算衰减值
	float dist = length(lightPosition - worldPosition);
	float attenuation = 1.0f / (kc + k1 * dist + k2 * dist * dist);

    //计算diffuse
	float diffuse = clamp(dot(-lightDirN,normalN),0.0f,1.0f);
	vec3 diffuseColor = lightColor * diffuse * objectColor;

	//计算specular
	//防止背面光效果
	float dotResult = dot(-lightDirN,normalN);
	float flag = step(0.0f,dotResult);
	vec3 lightReflect = normalize(reflect(lightDirN,normalN));
	float specular = max(dot(lightReflect,-viewDir),0.0f);
	specular = pow(specular,shiness);

	float specularMask = texture(specularMaskSampler,uv).r; // Assuming the specular mask is in the red channel

	vec3 specularColor = lightColor * specular * flag * specularIntensity * specularMask;

	//环境光计算
	vec3 ambientColor = objectColor * ambientColor;

	vec3 finalColor = (diffuseColor + specularColor) * attenuation + ambientColor;

	//FragColor = texture(sampler,uv);
	FragColor = vec4(finalColor,1.0f);
}