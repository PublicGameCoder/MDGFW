#include <Workspace\RGBAObj.h>
#include <MDGFW/Engine.h>

int main( void )
{
	Engine engine;

	World* world1 = new World();

	Line* line = new Line();

	Entity* pencils = new Entity();
	pencils->addSprite( "assets/pencils.tga" );
	pencils->position = Vector2( 400, 300 );
	pencils->scale = Vector2( 1, 1 );
	pencils->rotation = Vector3();
	pencils->addLine( line );

	Entity* kingkong = new Entity();
	kingkong->addSprite( "assets/kingkong.tga" );
	kingkong->position = Vector2( 900, 400 );
	kingkong->scale = Vector2( 1, 1 );
	kingkong->rotation = Vector3();

	RGBAObj* rgba = new RGBAObj();
	rgba->addSprite( "assets/rgba.tga" );
	rgba->position = Vector2( MINSWIDTH / 2, MINSHEIGHT / 2 );
	rgba->scale = Vector2( 1, 1 );
	rgba->rotation = Vector3();

	world1->addChild( pencils );
	world1->addChild( kingkong );
	world1->addChild( rgba );

	do {
		engine.run(world1);
	} // Check if the ESC key was pressed or the window was closed
	while( engine.isRunning() || !glfwWindowShouldClose(engine.getWindow()) == 0 );
	
	delete world1;//also removes pencils/kingkong and rgba

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
