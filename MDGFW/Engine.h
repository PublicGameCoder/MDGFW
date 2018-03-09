#ifndef ENGINE_H
#define ENGINE_H

// Include GLEW
#include <GL\glew.h>

// Include GLFW
#include <glfw3.h>

#include <MDGFW\renderer.h>
#include <MDGFW/camera.h>
#include <MDGFWConfig.h>

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void run( World* world );
	GLFWwindow* getWindow() {
		return _rend.window();
	}

	bool isRunning() {
		return _running;
	}

	void setRunning( bool state ) {
		_running = state;
	}

private:
	Renderer _rend;

	bool _running;
};

#endif // !ENGINE_H
