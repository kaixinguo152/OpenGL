#pragma once

#include "core.h"
#include<string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();

	void end();

	void setVector3(const std::string name, const glm::vec3 value);
	void setVector3(const std::string name, const float* values);
	void setVector3(const std::string name, float x, float y, float z);

	void setFloat(const std::string& name, float value) const;

	void setInt(const std::string& name, int value) const;

	void setMatrix3x3(const std::string& name, const glm::mat3& matrix) const;
	void setMatrix4x4(const std::string& name, const glm::mat4& matrix) const;

private:
	void checkCompileErrors(GLuint target, std::string type);

private:
	GLuint mProgram{ 0 };

};