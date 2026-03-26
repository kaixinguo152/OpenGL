#include"gameCameraControl.h"
#include<iostream>

gameCameraControl::gameCameraControl() :CameraControl() {}

gameCameraControl::~gameCameraControl() {}

void gameCameraControl::translateX(float speed) {
	mCamera->mPosition += speed * glm::normalize(mCamera->mRight);
}

void gameCameraControl::translateY(float speed) {
	mCamera->mPosition += speed * glm::normalize(mCamera->mUp);
}

void gameCameraControl::translateZ(float speed) {
	mCamera->mPosition += speed * mCamera->getFrontVector();
}

//void gameCameraControl::onCursor(double xpos, double ypos) {
//	std::cout << xpos - 375.0f << " " << ypos - 375.0f << std::endl;
//	mCurrentMouseX = xpos;
//	mCurrentMouseY = ypos;
//}

//void gameCameraControl::setViewDirection(float xpos, float ypos) {
//	glm::mat4 rotateMatrix;
//
//	float angleX = (xpos - 375.0f) / 750.0f * mSensitivity;
//	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(0.0f, 1.0f, 0.0f));
//	mCamera->mRight = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
//	//mCamera->mRight = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(mCamera->mRight, 0.0f)));
//
//	float angleY = (ypos - 375.0f) / 750.0f * mSensitivity;
//	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleY), glm::vec3(1.0f, 0.0f, 0.0f));
//	mCamera->mUp = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
//	//mCamera->mUp = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(mCamera->mUp, 0.0f)));
//}

void gameCameraControl::onCursor(double xpos, double ypos) {
	float offsetX = xpos - mLastMouseX;
	float offsetY = -(ypos - mLastMouseY);
	mLastMouseX = xpos, mLastMouseY = ypos;

	offsetX *= mSensitivity;
	offsetY *= mSensitivity;

	mCamera->mYaw += offsetX;
	mCamera->mPintch += offsetY;

	float pintchMax = 90.0f;
	float yawMax = 90.0f;
	if (mCamera->mPintch > pintchMax) mCamera->mPintch = pintchMax;
	if (mCamera->mYaw > yawMax) mCamera->mYaw = yawMax;

	glm::vec3 direction;
	direction.x = cos(glm::radians(mCamera->mYaw) * cos(glm::radians(mCamera->mPintch)));
	direction.y = sin(glm::radians(mCamera->mPintch));
	direction.z = sin(glm::radians(mCamera->mYaw) * cos(glm::radians(mCamera->mPintch)));
	mCamera->mFront = glm::normalize(direction);

	mCamera->mRight = glm::cross(mCamera->mFront, mCamera->mUp);
}

void gameCameraControl::processKeyInput() {
	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;

	float deltaStep = mMoveSpeed * deltaTime;

	if (mKeyMap[GLFW_KEY_LEFT_ALT]) {
		if (mKeyMap[GLFW_KEY_SPACE]) {
			translateY(-deltaStep);
		}
	}

	//右
	if (mKeyMap[GLFW_KEY_D]) {
		translateX(deltaStep);
		//std::cout << "upatde detected the key pressed" << std::endl;
		//std::cout << mCamera->mPosition.z<< std::endl;
	}
	//左
	if (mKeyMap[GLFW_KEY_A]) {
		translateX(-deltaStep);
	}
	//后
	if (mKeyMap[GLFW_KEY_S]) {
		translateZ(deltaStep);
	}
	//前
	if (mKeyMap[GLFW_KEY_W]) {
		translateZ(-deltaStep);
	}
	//上
	if (mKeyMap[GLFW_KEY_SPACE]) {
		translateY(deltaStep);
	}
	if (mKeyMap[GLFW_KEY_LEFT_CONTROL]) {
		translateY(-deltaStep);
	}
}

float transformMouseXPosition(float mouseXPos) {
	float halfWindowWidth = 375.0f;
	return mouseXPos - halfWindowWidth;
}
float transformMouseYPosition(float mouseYPos) {
	float halfWindowHeight = 375.0f;
	return -(mouseYPos - halfWindowHeight);
}

//void gameCameraControl::processCursorInput() {
//	glm::mat4 rotateMatrix;
//
//	float angleX = transformMouseXPosition(mCurrentMouseX) / 750.0f * mSensitivity;
//	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleX), glm::vec3(0.0f, 1.0f, 0.0f));
//	//mCamera->mRight = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
//	mCamera->mRight = glm::vec3(rotateMatrix * glm::vec4(mCamera->mRight, 0.0f));
//
//	float angleY = transformMouseYPosition(mCurrentMouseY) / 750.0f * mSensitivity;
//	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-angleY), glm::vec3(1.0f, 0.0f, 0.0f));
//	//mCamera->mUp = glm::normalize(glm::vec3(rotateMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
//	mCamera->mUp = glm::vec3(rotateMatrix * glm::vec4(mCamera->mUp, 0.0f));
//}

void gameCameraControl::update() {
	processKeyInput();

	//glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//mCamera->mRight = glm::vec3(rotation * glm::vec4(mCamera->mFront, 0.0f));

	//mCamera->mUp = glm::cross(mCamera->mFront, mCamera->mRight);
}