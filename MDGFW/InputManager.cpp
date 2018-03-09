#include "InputManager.h"

InputManager* InputManager::instance = NULL;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	InputManager::getManager()->scrollCallback(window, xoffset, yoffset);
}

void window_iconify_callback( GLFWwindow* window, int iconified );

InputManager::InputManager() {
	currentWindow = NULL;

	prevWindowWidth = 0;
	prevWindowHeight = 0;

	windowWidth = 0;
	windowHeight = 0;

	for (unsigned int i = 0; i<GLFW_KEY_LAST; i++) {
		PressedKeys[i] = false;
		KeysUp[i] = false;
		KeysDown[i] = false;
	}
	for (unsigned int i = 0; i<GLFW_MOUSE_BUTTON_LAST; i++) {
		mouse[i] = false;
		mouseUp[i] = false;
		mouseDown[i] = false;
	}
}

InputManager::~InputManager() {

}

InputManager* InputManager::getManager(void) {
	if (!InputManager::instance) {
		InputManager::instance = new InputManager();
	}
	return InputManager::instance;
}

void InputManager::preprocessWindow(GLFWwindow* window) {
	if (std::find(monitoredWindows.begin(), monitoredWindows.end(), window) == monitoredWindows.end()) {
		//When window isn't monitored.

		glfwSetScrollCallback(window, scroll_callback);

		monitoredWindows.push_back(window);
	}
}

void InputManager::update(GLFWwindow* w) {
	currentWindow = w;

	preprocessWindow(w);

	glfwPollEvents();

	glfwGetWindowSize(this->currentWindow, &windowWidth, &windowHeight);

	/*
	if (prevWindowWidth != windowWidth || prevWindowHeight != windowHeight) {
		EventHandler::getManager()->call(WindowResizeEvent(currentWindow, windowWidth, windowHeight));
		prevWindowWidth = windowWidth;
		prevWindowHeight = windowHeight;
	}*/

	glfwSetWindowIconifyCallback( this->currentWindow, window_iconify_callback );

	glfwGetCursorPos(this->currentWindow, &mouseX, &mouseY);

	mouseX = ((float)MINSWIDTH / windowWidth) * mouseX;
	mouseY = ((float)MINSHEIGHT / windowHeight) * mouseY;

	for (unsigned int i = 32; i<97; i++) {
		processKey(i);
	}
	for (unsigned int i = 255; i<GLFW_KEY_LAST; i++) {
		processKey(i);
	}

	for (unsigned int i = 0; i<GLFW_MOUSE_BUTTON_LAST; i++) {
		processButton(i);
	}
}

void InputManager::processKey(unsigned int key) {
	if (glfwGetKey(this->currentWindow, key) == GLFW_PRESS) {
		if (!PressedKeys[key]) {
			PressedKeys[key] = true;
			KeysDown[key] = true;
			KeysUp[key] = false;
		}
		else {
			KeysDown[key] = false;
		}
	}
	if (glfwGetKey(this->currentWindow, key) == GLFW_RELEASE) {
		if (PressedKeys[key]) {
			PressedKeys[key] = false;
			KeysUp[key] = true;
			KeysDown[key] = false;
		}
		else {
			KeysUp[key] = false;
		}
	}
}

void InputManager::processButton(unsigned int button) {
	if (glfwGetMouseButton(this->currentWindow, button) == GLFW_PRESS) {
		if (mouse[button] == false) {
			mouse[button] = true;
			mouseDown[button] = true;
			mouseUp[button] = false;
		}
		else {
			mouseDown[button] = false;
		}
	}
	if (glfwGetMouseButton(this->currentWindow, button) == GLFW_RELEASE) {
		if (mouse[button] == true) {
			mouse[button] = false;
			mouseUp[button] = true;
			mouseDown[button] = false;
		}
		else {
			mouseUp[button] = false;
		}
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (horizontalScrolls.find(window) == horizontalScrolls.end()) {
		horizontalScrolls.insert(std::pair<GLFWwindow*, int>(window, (xoffset > 0) ? 1 : -1));
	}
	else {
		horizontalScrolls.find(window)->second = (xoffset > 0) ? 1 : -1;
	}

	if (verticalScrolls.find(window) == verticalScrolls.end()) {
		verticalScrolls.insert(std::pair<GLFWwindow*, int>(window, (yoffset > 0) ? 1 : -1));
	}
	else {
		verticalScrolls.find(window)->second = (yoffset > 0) ? 1 : -1;
	}

	if (continuedHorizontalScrolls.find(window) == continuedHorizontalScrolls.end()) {
		continuedHorizontalScrolls.insert(std::pair<GLFWwindow*, int>(window, (xoffset > 0) ? 1 : -1));
	}
	else {
		continuedHorizontalScrolls.find(window)->second += (xoffset > 0) ? 1 : -1;
	}

	if (continuedVerticalScrolls.find(window) == continuedVerticalScrolls.end()) {
		continuedVerticalScrolls.insert(std::pair<GLFWwindow*, int>(window, (yoffset > 0) ? 1 : -1));
	}
	else {
		continuedVerticalScrolls.find(window)->second += (yoffset > 0) ? 1 : -1;
	}
}

void window_iconify_callback( GLFWwindow* window, int iconified )
{
	if ( iconified )
	{
		// The window was iconified
		Time::pause();
	}
	else
	{
		// The window was restored
		Time::unpause();
	}
}