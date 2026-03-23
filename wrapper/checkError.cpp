#include"checkError.h"
#include <glad/glad.h>
#include<iostream>
//#include<string>

void checkError() {
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}
}