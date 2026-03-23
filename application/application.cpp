#include"Application.h"

Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Application();
	}
	return mInstance;
}

Application::Application() {
}

Application::~Application() {
	//delete Application::mInstance;
	//Application::mInstance = nullptr;
}

bool Application::init(const int& width, const int& height) {
	mWindowWidth = width;
	mWindowHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//设置opengl启用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return false;
	}

	return true;
}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	glfwPollEvents();
	glfwSwapBuffers(mWindow);

	glfwSetWindowUserPointer(mWindow, this);

	//鼠标点击时间响应
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	//鼠标移动事件响应
	glfwSetCursorPosCallback(mWindow, cursorCallback);

	glfwSetKeyCallback(mWindow, keyboardCallback);
	return true;
}

void Application::destroy() {
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Application::getCursorPosition(double* xpos, double* ypos) {
	glfwGetCursorPos(mWindow, xpos, ypos);
}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	Application* self = Application::getInstance();
	if (self->mouseCallback != nullptr) {
		self->mMouseCallback(button, action, mods);
	}
};
void Application::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	Application* self = Application::getInstance();
	if (self->cursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
};

void Application::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* self = Application::getInstance();
	if (self->cursorCallback != nullptr) {
		self->mKeyboardCallback(window, key, scancode, action, mods);
	}
};