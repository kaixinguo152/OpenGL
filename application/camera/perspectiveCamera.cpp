#include"perspectiveCamera.h"

perspectiveCamera::perspectiveCamera(float fov, float aspect, float n, float f) {
	mFov = fov;
	mAspect = aspect;
	mNear = n;
	mFar = f;
};
perspectiveCamera:: ~perspectiveCamera() {};
glm::mat4 perspectiveCamera::getProjectionMatrix() {
	return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
};