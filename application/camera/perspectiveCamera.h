#pragma once 

#include"camera.h"

class perspectiveCamera : public Camera {
public:
	perspectiveCamera(float fov, float aspect, float n, float f);
	~perspectiveCamera();
	glm::mat4 getProjectionMatrix() override;
public:
	float mFov = 0.0f;
	float mAspect = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;
};