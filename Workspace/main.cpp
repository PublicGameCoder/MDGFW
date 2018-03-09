#include <MDGFW/Engine.h>

int main( void )
{
	Engine engine;

	World* world1 = new World();

	Sprite* pencils = new Sprite("assets/pencils.tga");
	Sprite* kingkong = new Sprite("assets/kingkong.tga");
	Sprite* rgba = new Sprite("assets/rgba.tga");

	world1->addSprite( pencils );
	world1->addSprite( kingkong );
	world1->addSprite( rgba );

	do {

		engine.run(world1);

	} // Check if the ESC key was pressed or the window was closed
	while( engine.isRunning() || !glfwWindowShouldClose(engine.getWindow()) == 0 );
	
	delete world1;
	delete pencils;
	delete kingkong;
	delete rgba;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
