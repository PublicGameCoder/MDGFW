#include "Engine.h"

Engine::Engine() {
	_running = true;
}

Engine::~Engine() {

}

void Engine::run(Scene* world) {

	InputManager::getManager()->update( _rend.window() );

	Time::calcDelta();

	if ( InputManager::getManager()->getKeyDown( KeyCode::Esc ) ) {
		setRunning( false );
		return; //Prevent loop to render the screen ones more before closing.
	}
	if ( world == nullptr ) {
		_sceneManager.update();
		world = _sceneManager.getCurrent();
	}
	_rend.updateWorld( world );
}