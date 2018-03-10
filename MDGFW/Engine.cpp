#include "Engine.h"

Engine::Engine() {
	_running = true;
}

Engine::~Engine() {

}

void Engine::run(World* world) {

	InputManager::getManager()->update( _rend.window() );

	Time::calcDelta();

	if ( InputManager::getManager()->getKeyDown( KeyCode::Esc ) ) {
		setRunning( false );
	}
	_rend.updateWorld( world );
}