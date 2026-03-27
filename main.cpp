#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include<iostream>
#include"glframework/core.h"
#include"glframework/shader.h"
#include<assert.h>
#include"wrapper/checkError.h"
#include"application/Application.h"
#include"glframework/texture.h"

#include"glframework/geometry.h"
#include"glframework/material/PhongMaterial.h"
#include"glframework/mesh.h"
#include"glframework/renderer/renderer.h"

//引入相机和控制器
#include"application/camera/perspectiveCamera.h"
#include"application/camera/gameCameraControl.h"

#include"glframework/geometry.h"

Renderer* renderer = nullptr;
std::vector<Mesh*> meshes{};
DirectionalLight* dirLight = nullptr;
AmbientLight* ambLight = nullptr;

perspectiveCamera* camera = nullptr;
gameCameraControl* cameraControl = nullptr;

glm::vec3 lightDirection = glm::vec3(-1.0f, -1.0f, -1.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

//鼠标按下/抬起
void OnMouse(int button, int action, int mods) {
	//std::cout << "mouse click" << button << " " << action << std::endl;
	double x, y;
	app->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, mods, x, y);
}

void OnCursor(double xpos, double ypos) {
	//std::cout << xpos << " " << ypos << std::endl;
	//constexpr float angle_of_view = glm::radians(60.0f);
	//std::cout << xpos - app->getWindowWidth() / 2 << std::endl;
	//float angle = (xpos - app->getWindowWidth() / 2) / app->getWindowWidth() * angle_of_view;
	//viewMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	cameraControl->onCursor(xpos, ypos);
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//if (key == GLFW_KEY_W && action == GLFW_PRESS) {
	//	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -0.01f, 0.0f));
	//}
	//else return;
	cameraControl->onKey(key, scancode, action, mods);
}

void prepareCamera() {
	camera = new perspectiveCamera(
		60.0f,
		(float)app->getWindowWidth() / (float)app->getWindowHeight(),
		0.1f,
		1000.0f
	);

	cameraControl = new gameCameraControl();
	cameraControl->setCamera(camera);
}

void prepare() {
	renderer = new Renderer();

	auto geometry = Geometry::createSphere(1.0f);

	auto material = new PhongMaterial();
	material->mShiness = 32.0f;
	material->mDiffuse = new Texture("./assets/textures/earth.jpg", 0);

	auto mesh = new Mesh(geometry, material);
	meshes.push_back(mesh);

	dirLight = new DirectionalLight();
	dirLight->mDirection = glm::vec3(-1.0f);
	dirLight->mColor = glm::vec3(1.0f);
	dirLight->mSpecularIntensity = 0.7f;
	ambLight = new AmbientLight();
	ambLight->mColor = glm::vec3(0.15f);
}

int main(void) {
	app->init(750, 750);

	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);

	//设置键盘响应事件
	app->setKeyboardCallback(OnKey);
	//设置鼠标响应事件
	app->setCursorCallback(OnCursor);

	prepareCamera();
	prepare();

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	while (app->update()) {
		cameraControl->update();
		renderer->render(meshes, camera, dirLight, ambLight);
	}
	app->destroy();
	return 0;
}