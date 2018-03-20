#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glfw3.h>
#include <map>
#include <vector>

#include <MDGFW\MDGTime.h>
#include <MDGFW\MDGFWConfig.h>

enum KeyCode;
class InputManager {
public:
	static InputManager* getManager(void);

	void update(GLFWwindow* window);

	virtual ~InputManager();

	void setMouse(double xPos, double yPos) { glfwSetCursorPos(currentWindow, xPos, yPos); };

	int getWindowWidth() { return windowWidth; }
	int getWindowHeight() { return windowHeight; }

	bool getKey(KeyCode key) { return PressedKeys[(unsigned int)key]; }
	bool getKey(int key) { return getKey((KeyCode)key); }
	bool getKey(char key) { return getKey((KeyCode)key); }

	bool getKeyDown(KeyCode key) { return KeysDown[(unsigned int)key]; }
	bool getKeyDown(int key) { return getKeyDown((KeyCode)key); }
	bool getKeyDown(char key) { return getKeyDown((KeyCode)key); }

	bool getKeyUp(KeyCode key) { return KeysUp[(unsigned int)key]; }
	bool getKeyUp(int key) { return getKeyUp((KeyCode)key); }
	bool getKeyUp(char key) { return getKeyUp((KeyCode)key); }

	bool getMouse(unsigned int button) { return mouse[button]; }
	bool getMouseDown(unsigned int button) { return mouseDown[button]; }
	bool getMouseUp(unsigned int button) { return mouseUp[button]; }

	double getMouseX() { return mouseX; }
	double getMouseY() { return mouseY; }

	int getScrollVertical(GLFWwindow* window) { return (verticalScrolls.find(window) != verticalScrolls.end())?verticalScrolls.find(window)->second : 0; }
	int getScrollHorizontal(GLFWwindow* window) { return (horizontalScrolls.find(window) != horizontalScrolls.end()) ? horizontalScrolls.find(window)->second : 0; }
	int getScrollVerticalContinued(GLFWwindow* window) { return (continuedVerticalScrolls.find(window) != continuedVerticalScrolls.end()) ? continuedVerticalScrolls.find(window)->second : 0; }
	int getScrollHorizontalContinued(GLFWwindow* window) { return (continuedHorizontalScrolls.find(window) != continuedHorizontalScrolls.end()) ? continuedHorizontalScrolls.find(window)->second : 0; }

	void resetScrollVertical(GLFWwindow* window) { continuedVerticalScrolls.find(window)->second = 0; }
	void resetScrollHorizontal(GLFWwindow* window) { continuedHorizontalScrolls.find(window)->second = 0; }

	GLFWwindow* getWindow() {
		return currentWindow;
	}

	void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	static InputManager* instance;

	GLFWwindow* currentWindow;
	bool PressedKeys[GLFW_KEY_LAST];
	bool KeysUp[GLFW_KEY_LAST];
	bool KeysDown[GLFW_KEY_LAST];

	bool mouse[GLFW_MOUSE_BUTTON_LAST];
	bool mouseUp[GLFW_MOUSE_BUTTON_LAST];
	bool mouseDown[GLFW_MOUSE_BUTTON_LAST];

	double mouseX;
	double mouseY;

	int prevWindowWidth;
	int prevWindowHeight;

	int windowWidth;
	int windowHeight;

	void preprocessWindow(GLFWwindow* window);
	std::vector<GLFWwindow*> monitoredWindows;

	//Latest scroll direction
	std::map<GLFWwindow*,int> verticalScrolls;
	//Total Amount of scrolls from reset
	std::map<GLFWwindow*,int> continuedVerticalScrolls;
	
	std::map<GLFWwindow*,int> horizontalScrolls;
	std::map<GLFWwindow*,int> continuedHorizontalScrolls;

	void processKey(unsigned int key);
	void processButton(unsigned int button);

	InputManager();
};

enum KeyCode
{
	Space = 32,
	Apostrophe = 39,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Alpha0 = 48,
	Alpha1 = 49,
	Alpha2 = 50,
	Alpha3 = 51,
	Alpha4 = 52,
	Alpha5 = 53,
	Alpha6 = 54,
	Alpha7 = 55,
	Alpha8 = 56,
	Alpha9 = 57,
	Semicolon = 59,
	Equal = 61,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	GraveAccent = 96,
	Esc = 256,
	Enter = 257,
	Tab = 258,
	Backspace = 259,
	Insert = 260,
	Delete = 261,
	Right = 262,
	Left = 263,
	Down = 264,
	Up = 265,
	PageUp = 266,
	PageDown = 267,
	Home = 268,
	End = 269,
	CapsLock = 280,
	ScrollLock = 281,
	NumLock = 282,
	PrintScreen = 283,
	Pause = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,
	KeyPad0 = 320,
	KeyPad1 = 321,
	KeyPad2 = 322,
	KeyPad3 = 323,
	KeyPad4 = 324,
	KeyPad5 = 325,
	KeyPad6 = 326,
	KeyPad7 = 327,
	KeyPad8 = 328,
	KeyPad9 = 329,
	KeyPadDecimal = 330,
	KeyPadDivide = 331,
	KeyPadMultiply = 332,
	KeyPadSubtract = 333,
	KeyPadAdd = 334,
	KeyPadEnter = 335,
	KeyPadEqual = 336,
	LeftShift = 340,
	LeftControl = 341,
	LeftAlt = 342,
	LeftSuper = 343,
	RightShift = 344,
	RightControl = 345,
	RightAlt = 346,
	RightSuper = 347,
	Menu = 348
};

#endif // !INPUTMANAGER_H
