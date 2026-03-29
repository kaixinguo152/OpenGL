#pragma once

#include"../../glframework/core.h"

class Camera {
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix() const;
	glm::vec3 getFrontVector() const;
	virtual glm::mat4 getProjectionMatrix();

	void setPosition(const glm::vec3& pos) { mPosition = pos; }
public:
	glm::vec3 mPosition{ 0.0f,0.0f,2.0f };
	glm::vec3 mFront{ -1.0f,0.0f,0.0f };
	glm::vec3 mUp{ 0.0f,1.0f, 0.0f };
	glm::vec3 mRight{ 1.0f,0.0f,0.0f };

	float mYaw{ -90.0f };
	float mPintch{ 0.0f };
};