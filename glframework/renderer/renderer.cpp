#include"renderer.h"
#include<iostream>
#include"../material/PhongMaterial.h"
#include"../material/whiteMaterial.h"

Renderer::Renderer() {
	mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
	mWhiteShader = new Shader("assets/shaders/white.vert", "assets/shaders/white.frag");
}

Renderer::~Renderer() {

}

void Renderer::render(
	const std::vector<Mesh*>& meshes,
	Camera* camera,
	PointLight* pointLight,
	AmbientLight* ambLight
) {
	//设置opengl必要状态机参数
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//清理画布
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//遍历mesh进行绘制
	for (int i = 0; i < meshes.size(); i++) {
		auto mesh = meshes[i];
		auto geometry = mesh->mGeometry;
		auto material = mesh->mMaterial;

		//1.决定使用那个shader
		Shader* shader = pickShader(material->mType);
		//2.更新shader中的uniform
		shader->begin();

		switch (material->mType) {
		case MaterialType::PhongMaterial: {
			PhongMaterial* phongMat = (PhongMaterial*)material;
			//diffuse贴图
			//将纹理采样器和纹理单元绑定
			shader->setInt("sampler", 0);
			//将纹理和纹理单元绑定
			phongMat->mDiffuse->bind();

			//高光蒙版帧更新
			shader->setInt("specularMaskSampler", 1);
			phongMat->mSpecularMask->bind();

			//mvp变换矩阵
			shader->setMatrix4x4("modelMatrix", mesh->getModelMatrix());
			shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());//设置相机矩阵
			shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());//设置投影矩阵

			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
			shader->setMatrix3x3("normalMatrix", normalMatrix);

			//更新光照参数
			//shader->setVector3("lightDirection", dirLight->mDirection);
			shader->setVector3("lightPosition", pointLight->getPosition());
			shader->setVector3("lightColor", pointLight->mColor);
			shader->setFloat("specularIntensity", pointLight->mSpecularIntensity);
			shader->setFloat("k2", pointLight->mK2);
			shader->setFloat("k1", pointLight->mK1);
			shader->setFloat("kc", pointLight->mKc);

			shader->setFloat("shiness", phongMat->mShiness);
			shader->setVector3("ambientColor", ambLight->mColor);

			//相机信息更新
			shader->setVector3("cameraPosition", camera->mPosition);
			break;
		}
		case MaterialType::WhiteMaterial: {
			WhiteMaterial* whiteMat = (WhiteMaterial*)material;

			//mvp变换矩阵
			shader->setMatrix4x4("modelMatrix", mesh->getModelMatrix());
			shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());//设置相机矩阵
			shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());//设置投影矩阵
			break;
		}
		default:
			continue;
		}

		//3.绑定vao
		glBindVertexArray(geometry->getVao());
		//4.绘制
		glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
}

Shader* Renderer::pickShader(MaterialType type) {
	Shader* result = nullptr;
	switch (type) {
	case MaterialType::PhongMaterial:
		result = mPhongShader;
		break;
	case MaterialType::WhiteMaterial:
		result = mWhiteShader;
		break;
	default:
		std::cout << "Unkonwn material type to pick shader" << std::endl;
		break;
	}

	return result;
}

//void Renderer::render(
//	const std::vector<Mesh*>& meshes,
//	Camera* camera,
//	PointLight* pointLight,
//	AmbientLight* ambLight
//) {
//	//设置opengl必要状态机参数
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//	//清理画布
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//遍历mesh进行绘制
//	for (int i = 0; i < meshes.size(); i++) {
//		auto mesh = meshes[i];
//		auto geometry = mesh->mGeometry;
//		auto material = mesh->mMaterial;
//
//		//1.决定使用那个shader
//		Shader* shader = pickShader(material->mType);
//		//2.更新shader中的uniform
//		shader->begin();
//
//		switch (material->mType) {
//		case MaterialType::PhongMaterial: {
//			PhongMaterial* phongMat = (PhongMaterial*)material;
//			//diffuse贴图
//			//将纹理采样器和纹理单元绑定
//			shader->setInt("sampler", 0);
//			//将纹理和纹理单元绑定
//			phongMat->mDiffuse->bind();
//
//			//高光蒙版帧更新
//			shader->setInt("specularMaskSampler", 1);
//			phongMat->mSpecularMask->bind();
//
//			//mvp变换矩阵
//			shader->setMatrix4x4("modelMatrix", mesh->getModelMatrix());
//			shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());//设置相机矩阵
//			shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());//设置投影矩阵
//
//			auto normalMatrix = glm::mat3(glm::transpose(glm::inverse(mesh->getModelMatrix())));
//			shader->setMatrix3x3("normalMatrix", normalMatrix);
//
//			//更新光照参数
//			shader->setVector3("lightDirection", dirLight->mDirection);
//			shader->setVector3("lightPosition", pointLight->getPosition());
//			shader->setVector3("directionLightColor", dirLight->mColor);
//			shader->setVector3("pointLightColor", pointLight->mColor);
//			shader->setFloat("specularIntensity", dirLight->mSpecularIntensity);
//			shader->setFloat("k2", pointLight->mK2);
//			shader->setFloat("k1", pointLight->mK1);
//			shader->setFloat("kc", pointLight->mKc);
//
//			shader->setFloat("shiness", phongMat->mShiness);
//			shader->setVector3("ambientColor", ambLight->mColor);
//
//			//相机信息更新
//			shader->setVector3("cameraPosition", camera->mPosition);
//			break;
//		}
//		case MaterialType::WhiteMaterial: {
//			WhiteMaterial* whiteMat = (WhiteMaterial*)material;
//
//			//mvp变换矩阵
//			shader->setMatrix4x4("modelMatrix", mesh->getModelMatrix());
//			shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());//设置相机矩阵
//			shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());//设置投影矩阵
//			break;
//		}
//		default:
//			continue;
//		}
//
//		//3.绑定vao
//		glBindVertexArray(geometry->getVao());
//		//4.绘制
//		glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);
//	}
//}