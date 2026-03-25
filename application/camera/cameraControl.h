#pragma once

#include"camera.h"
#include<map>

class CameraControl {
public:
	CameraControl();
	~CameraControl();

	void getCamera(Camera* camera) { this->mCamera = camera; }

	virtual void onMouse(int button, int action, int mods, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int scancode, int action, int mods);

	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }
protected:
	bool mLeftMousePressed = false;
	bool mRightMousePressed = false;
	bool mMiddleMousePressed = false;
	float mCurrentMouseX = 0.0f, mCurrentMouseY = 0.0f;
	std::map<int, bool>mKeyMap;
	float mSensitivity = 0.1f;
	Camera* mCamera = nullptr;

};
