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

private:
	GLfloat mMoveSpeed{ 0.0001f };
};