#pragma once
#include<vector>
#include"../core.h"
#include"../mesh.h"
#include"../../application/camera/camera.h"
#include"../light/directionalLight.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	//渲染功能函数
	void render(
		const std::vector<Mesh*>& meshes,
		Camera* camera,
		DirectionLight* dirLight
	);
private:

};