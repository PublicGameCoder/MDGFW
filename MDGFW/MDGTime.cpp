#include "MDGTime.h"

float Time::deltaTime = 0;
bool Time::_paused = false;
bool Time::_prevState = false;

void Time::calcDelta() {

	if ( _prevState != _paused && _paused ) {
		std::cout << "Paused!" << std::endl;
	}

	if ( _prevState != _paused && !_paused ) {
		std::cout << "UnPaused!" << std::endl;
	}

	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	deltaTime = float( startTime - lastTime );
	lastTime = startTime;

	if ( _paused ) {
		deltaTime = 0.0f;
	}

	_prevState = _paused;
}