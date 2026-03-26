#include"camera.h"

Camera::Camera() {
};
Camera::~Camera() {
};

glm::mat4 Camera::getViewMatrix() const {
	//glm::vec3 front = glm::cross(mUp, mRight);
	//glm::vec3 center = mPosition + front;

	glm::vec3 center = mPosition + mFront;

	return glm::lookAt(mPosition, center, mUp);
};

glm::mat4 Camera::getProjectionMatrix() {
	return glm::identity<glm::mat4>();
};

glm::vec3 Camera::getFrontVector() const{
	return glm::normalize(glm::cross(mRight,mUp));
}
