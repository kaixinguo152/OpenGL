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

private:
	GLfloat mMoveSpeed{ 0.005f };
};