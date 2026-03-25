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

void gameCameraControl::update() {
	if (mKeyMap[GLFW_KEY_LEFT_ALT]) {
		if (mKeyMap[GLFW_KEY_SPACE]) {
			translateY(-mMoveSpeed);
		}
	}
	if (mKeyMap[GLFW_KEY_D]) {
		translateX(mMoveSpeed);
		//std::cout << "upatde detected the key pressed" << std::endl;
		//std::cout << mCamera->mPosition.z<< std::endl;
	}
	if (mKeyMap[GLFW_KEY_A]) {
		translateX(-mMoveSpeed);
	}
	if (mKeyMap[GLFW_KEY_S]) {
		translateZ(mMoveSpeed);
	}
	if (mKeyMap[GLFW_KEY_W]) {
		translateZ(-mMoveSpeed);
	}
	if (mKeyMap[GLFW_KEY_SPACE]) {
		translateY(mMoveSpeed);
	}
	//if (mKeyMap[GLFW_KEY_LEFT_CONTROL]) {
	//	translateY(-mMoveSpeed);
	//}
}