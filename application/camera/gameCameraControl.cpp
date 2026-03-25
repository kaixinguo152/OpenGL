#include"gameCameraControl.h"
#include<iostream>

gameCameraControl::gameCameraControl() :CameraControl() {}

gameCameraControl::~gameCameraControl() {}

void gameCameraControl::translateX(float delta) {
	mCamera->mPosition.x += delta;
}

void gameCameraControl::translateY(float delta) {
	mCamera->mPosition.y += delta;
}

void gameCameraControl::translateZ(float delta) {
	mCamera->mPosition.z += delta;
}

//void gameCameraControl::setViewDirection(float xpos, float ypos) {
//	if (xpos > mCurrentMouseX) {
//		glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-mSensitivity), glm::vec3(0.0f, 1.0f, 0.0f));
//		mCamera->mRight = rotateMatrix * glm::vec4(mCamera->mRight, 0.0f);
//	}
//	if (xpos < mCurrentMouseX) {
//		glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mSensitivity), glm::vec3(0.0f, 1.0f, 0.0f));
//		mCamera->mRight = rotateMatrix * glm::vec4(mCamera->mRight, 0.0f);
//	}
//}
//
void gameCameraControl::onCursor(double xpos, double ypos) {
	std::cout << xpos - 375.0f << " " << ypos - 375.0f << std::endl;
	mCurrentMouseX = xpos;
	mCurrentMouseY = ypos;
}

void gameCameraControl::setViewDirection(float xpos, float ypos) {
	glm::mat4 rotateMatrix;

	float angleX = (xpos - 375.0f)/750.0f * mSensitivity;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(0.0f, 1.0f, 0.0f));
	mCamera->mRight = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));

	float angleY = (ypos - 375.0f)/750.0f * mSensitivity;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleY), glm::vec3(1.0f, 0.0f, 0.0f));
	mCamera->mUp = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
}

void gameCameraControl::update() {
	setViewDirection(mCurrentMouseX, mCurrentMouseY);

	if (mKeyMap[GLFW_KEY_LEFT_ALT]) {
		if (mKeyMap[GLFW_KEY_SPACE]) {
			translateY(-mMoveSpeed);
		}
	}

	//右
	if (mKeyMap[GLFW_KEY_D]) {
		translateX(mMoveSpeed);
		//std::cout << "upatde detected the key pressed" << std::endl;
		//std::cout << mCamera->mPosition.z<< std::endl;
	}
	//左
	if (mKeyMap[GLFW_KEY_A]) {
		translateX(-mMoveSpeed);
	}
	//后
	if (mKeyMap[GLFW_KEY_S]) {
		translateZ(mMoveSpeed);
	}
	//前
	if (mKeyMap[GLFW_KEY_W]) {
		translateZ(-mMoveSpeed);
	}
	//上
	if (mKeyMap[GLFW_KEY_SPACE]) {
		translateY(mMoveSpeed);
	}
	if (mKeyMap[GLFW_KEY_LEFT_CONTROL]) {
		translateY(-mMoveSpeed);
	}
}