#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include<iostream>
#include"glframework/core.h"
#include"glframework/shader.h"
#include<assert.h>
#include"wrapper/checkError.h"
#include"application/Application.h"
#include"glframework/texture.h"

//引入相机和控制器
#include"application/camera/perspectiveCamera.h"
#include"application/camera/gameCameraControl.h"

#include"glframework/geometry.h"

glm::vec3 lightDirection = glm::vec3(-1.0f, -1.0f, -1.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
//specular
float specularInstensity = 0.7f;
//ambient
glm::vec3 ambientColor = glm::vec3(0.15f, 0.15f, 0.15f);

Geometry* geometry = nullptr;
Shader* shader = nullptr;

glm::mat4 transformGrass(1.0f);
glm::mat4 transformLand(1.0f);

Texture* textureGrass = nullptr;
Texture* textureLand = nullptr;
Texture* textureEarth = nullptr;

Texture* texture = nullptr;
glm::mat4 transform(1.0);
glm::mat4 viewMatrix(1.0f);
glm::mat4 orthoMatrix(1.0f);
glm::mat4 perspectiveMatrix(1.0f);

Texture* grassTexture = nullptr;
Texture* landTexture = nullptr;
Texture* noiseTexture = nullptr;

perspectiveCamera* camera = nullptr;
gameCameraControl* cameraControl = nullptr;

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

void preTransform() {
	transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
}

void doTransform() {
	//float angle = 1.0f;
	//transform = glm::identity<glm::mat4>();
	//transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));  

	float angle = -0.5f;
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}

void prepareVAO() {
	//geometry = Geometry::createBox(0.5f);
	geometry = Geometry::createSphere(0.5f);
	//geometry = Geometry::createPlane(0.8f, 0.6f);
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
	//texture = new Texture("./assets/textures/texture.jpeg", 0);
	textureGrass = new Texture("./assets/textures/grass.jpeg", 0);
	textureLand = new Texture("./assets/textures/land.jpeg", 0);
	textureEarth = new Texture("./assets/textures/earth.jpg", 0);
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

	viewMatrix = glm::lookAt(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void preparePerspective() {
	perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)app->getWindowWidth() / (float)app->getWindowHeight(), 0.1f, 100.0f);
}

void prepareOrtho() {
	orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glClearDepth(0.0f);
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	shader->begin();
	shader->setInt("sampler", 0);
	shader->setMatrix4x4("modelMatrix", transform);
	shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());//设置相机矩阵
	//shader->setMatrix4x4("viewMatrix", viewMatrix);
	shader->setMatrix4x4("projectionMatrix", perspectiveMatrix);//设置投影矩阵

	//更新光照参数
	shader->setVector3("lightDirection", lightDirection);
	shader->setVector3("lightColor", lightColor);
	shader->setFloat("specularIntensity", specularInstensity);
	shader->setVector3("ambientColor", ambientColor);

	shader->setVector3("cameraPosition", camera->mPosition);

	//shader->setFloat("time", glfwGetTime());
	//shader->setInt("grassSampler", 0);
	//shader->setInt("landSampler", 1);
	//shader->setInt("noiseSampler", 2);
	//shader->setFloat("width", texture->getWidth());
	//shader->setFloat("height", texture->getHeight());
	//shader->setMatrix4x4("transform", transform);
	textureEarth->bind();
	glBindVertexArray(geometry->getVao());
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);

	//textureGrass->bind();
	//transformGrass = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -1.0f));
	//shader->setMatrix4x4("transform", transformGrass);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	//glBindVertexArray(vao_square);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);

	shader->end();
}

int main(void) {
	app->init(750, 750);

	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);

	//prepareVao_square();
	//prepareShader_square();
	//prepareTexture_square();

	prepareVAO();
	//std::cout << geometry->getVao() << std::endl;
	prepareShader();
	prepareTexture();
	prepareCamera();
	//prepareOrtho();
	preparePerspective();
	prepareState();

	//设置键盘响应时间
	app->setKeyboardCallback(OnKey);
	//设置鼠标响应时间
	app->setCursorCallback(OnCursor);

	glViewport(0, 0, app->getWindowWidth(), app->getWindowHeight());
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	//doTransform();
	//doTranslationTransform();
	//doScaleTransform(); 
	//preTransform();
	while (app->update()) {
		doTransform();
		cameraControl->update();
		render();
	}

	delete texture;
	app->destroy();
	return 0;
}