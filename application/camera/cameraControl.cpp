#include"cameraControl.h"
#include<iostream>

CameraControl::CameraControl() {};
CameraControl::~CameraControl() {};

void CameraControl::onMouse(int button, int action, int mods, double xpos, double ypos) {
	bool pressed = action == GLFW_PRESS ? true : false;
	if (pressed) {
		mCurrentMouseX = xpos;
		mCurrentMouseY = ypos;
	}

	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMousePressed = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMousePressed = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMousePressed = pressed;
		break;
	}
};
void CameraControl::onCursor(double xpos, double ypos) {

};
void CameraControl::onKey(int key, int scancode, int action, int mods) {
	if (action == GLFW_REPEAT) {
		return;
	}

	bool pressed = action == GLFW_PRESS ? true : false;

	//std::cout << "you pressed" << key << std::endl;
	mKeyMap[key] = pressed;
	//std::cout << mKeyMap[key] << std::endl;
};

void CameraControl::update() {};