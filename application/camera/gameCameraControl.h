#pragma once
#include "cameraControl.h"

class gameCameraControl : public CameraControl {
public:
	gameCameraControl();
	~gameCameraControl();

	void update() override;
	void translateX(float delta);
	void translateY(float delta);
	void translateZ(float delta);

	void onCursor(double xpos, double ypos) override;
	void setViewDirection(float xpos,float ypos);

	void processKeyInput();
	void processCursorInput();

private:
	GLfloat mMoveSpeed{ 1.0f };

	float mLastFrame{ 0.0f };
};