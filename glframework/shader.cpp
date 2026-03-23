#include"shader.h"
#include"../wrapper/checkError.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();
	//create shader program
	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	//insert shader source code to shader objects
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
	//compile shader objects
	int success = 0;
	char infoLog[1024];
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//create shader program and link shader objects to shader program
	mProgram = glCreateProgram();

	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);
	glLinkProgram(mProgram);
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mProgram, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

};

Shader::~Shader() {};

void Shader::begin() {
	GL_CALL(glUseProgram(mProgram));
};

void Shader::end() {
	GL_CALL(glUseProgram(0));
};

void Shader::setVector3(const std::string name, glm::vec3 value) {
	GLint location = glGetUniformLocation(mProgram, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}
void Shader::setVector3(const std::string name, const float* values) {
	GLint location = glGetUniformLocation(mProgram, name.c_str());
	glUniform3fv(location, 1, values);
}
void Shader::setVector3(const std::string name, float x, float y, float z) {
	GLint location = glGetUniformLocation(mProgram, name.c_str());
	glUniform3f(location, x, y, z);
}

void Shader::checkCompileErrors(GLuint target, std::string type) {
	int success = 0;
	char infoLog[1024];
	if (type == "COMPLIE") {
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "\n" << infoLog << std::endl;
		}
	}
	else if (type == "LINK") {
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mProgram, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	else {
		std::cout << "Error: Check shader errors Type is wrong" << std::endl;
	}
};

void Shader::setFloat(const std::string& name, float value) const {
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));

	GL_CALL(glUniform1f(location, value));
};

void Shader::setInt(const std::string& name, int value) const {
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	GL_CALL(glUniform1i(location, value));
};

void Shader::setMatrix4x4(const std::string& name, const glm::mat4& matrix) const {
	GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
};
