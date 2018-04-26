#include <MDGFW/Engine.h>
#include <Workspace/Player.h>

int main( void )
{
	Engine engine;//Needed to initialize engine.

	//World 1
	Scene* scene1 = new Scene();
	scene1->addSkybox( "skyboxes/mp_alpha/alpha-island_rt.png" , "skyboxes/mp_alpha/alpha-island_lf.png" , "skyboxes/mp_alpha/alpha-island_up.png" , "skyboxes/mp_alpha/alpha-island_dn.png" , "skyboxes/mp_alpha/alpha-island_ft.png" , "skyboxes/mp_alpha/alpha-island_bk.png" );
	SceneManager::addScene( scene1 );

	Player* player = new Player();

	do {
		engine.run( nullptr );//Needed to run game.

		if ( InputManager::getManager()->getKey(KeyCode::Space) ) {
			player->getAnimator()->Play();
		}

	} // Check if the ESC key was pressed or the window was closed
	while( engine.isRunning() );

	delete scene1;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
