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

	if ( Time::deltaTime == 0.0f ) return;

	static int windowed = true;
	if ( InputManager::getManager()->getKeyDown(KeyCode::F11) ) {
		if ( windowed ) {
			glfwWindowHint( GLFW_DECORATED, false );
		}else {
			glfwWindowHint( GLFW_DECORATED, true );
		}
	}

	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	_rend.updateWorld( world );

	// Compute the ViewMatrix from keyboard and mouse input (see: camera.h/cpp)
	computeMatricesFromInputs( _rend.window() );

	//glm::vec3 cursor = getCursor(); // from Camera
	//printf("(%f,%f)\n",cursor.x, cursor.y);

	std::vector<Sprite*> sprites = world->getSprites();

	static float rot_z = 0.0f;

	// Render all Sprites (Sprite*, xpos, ypos, xscale, yscale, rotation)
	_rend.renderSprite( sprites[0], 400, 300, 1.0f, 1.0f, 0.0f );
	_rend.renderSprite( sprites[1], 900, 400, 1.0f, 1.0f, 0.0f );
	_rend.renderSprite( sprites[2], InputManager::getManager()->getWindowWidth() / 2, InputManager::getManager()->getWindowHeight() / 2, 3.0f, 3.0f, rot_z );
	rot_z += (0.3f * Time::deltaTime);

	// Swap buffers
	glfwSwapBuffers( _rend.window() );
	glfwPollEvents();
}