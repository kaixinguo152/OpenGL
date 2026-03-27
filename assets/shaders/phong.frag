#version 330 core
out vec4 FragColor;

//in vec3 color;
in vec2 uv;
in vec3 normal;
in vec3 worldPosition;

uniform float width;
uniform float height;

uniform sampler2D sampler;

//光源参数
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform float specularIntensity;
uniform vec3 ambientColor; 

uniform vec3 cameraPosition;

void main()
{
	//FragColor = vec4(color,1.0f);
	//FragColor = texture(sampler, uv);

	//vec2 location = uv*vec2(width,height);

	//vec2 dx = dFdx(location);
	//vec2 dy = dFdy(location);

	//float maxDelta = sqrt(max(dot(dx,dx), dot(dy,dy)));
	//float L = log2(maxDelta);

	//int level = max(int(L+0.5), 0); // Round to nearest mip level, ensuring it's non-negative

	//FragColor = textureLod(sampler, uv, level);
	vec3 objectColor = texture(sampler,uv).xyz;
	vec3 normalN = normalize(normal);
	vec3 lightDirN = normalize(lightDirection);
	vec3 viewDir = normalize(worldPosition - cameraPosition);

	//计算diffuse
	float diffuse = clamp(dot(-lightDirN,normalN),0.0f,1.0f);
	vec3 diffuseColor = lightColor * diffuse * objectColor;

	//计算specular
	//防止背面光效果
	float dotResult = dot(-lightDirN,normalN);
	float flag = step(0.0f,dotResult);
	vec3 lightReflect = normalize(reflect(lightDirN,normalN));
	float specular = max(dot(lightReflect,-viewDir),0.0f);
	specular = pow(specular,10);
	vec3 specularColor = lightColor * specular * flag * specularIntensity;

	//环境光计算
	vec3 ambientColor = objectColor * ambientColor;

	vec3 finalColor = diffuseColor + specularColor + ambientColor;

	//FragColor = texture(sampler,uv);
	FragColor = vec4(finalColor,1.0f);
}