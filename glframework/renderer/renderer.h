#pragma once
#include<vector>
#include"../core.h"
#include"../mesh.h"
#include"../../application/camera/camera.h"
#include"../light/directionalLight.h"
#include"../light/ambientLight.h"
#include"../shader.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	//渲染功能函数
	void render(
		const std::vector<Mesh*>& meshes,
		Camera* camera,
		DirectionalLight* dirLight,
		AmbientLight* ambLight
	);
private:
	//根据material类型挑选shader
	Shader* pickShader(MaterialType type);
private:
	Shader* mPhongShader{ nullptr };
	Shader* mBShader{ nullptr };
};