#version 330 core
out vec4 FragColor;

uniform sampler2D sampler;

//in vec3 color;
in vec2 uv;

uniform float width;
uniform float height;

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

	FragColor = texture(sampler,uv);
}