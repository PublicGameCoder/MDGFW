#include <MDGFW/Engine.h>

int main( void )
{
	Engine engine;

	//World 1
	Scene* scene1 = new Scene();

	Entity* pencils = new Entity();
	pencils->addSprite( "assets/awesomeface.png" );
	pencils->position = Vector2( 400, 300 );
	pencils->scale = Vector2( 1, 1, 1 );
	pencils->rotation = Vector3();
	
	Entity* kingkong = new Entity();
	kingkong->addSprite( "assets/wall.jpg" );
	kingkong->position = Vector2( 900, 400 );
	kingkong->scale = Vector2( 1, 1, 1 );
	kingkong->rotation = Vector3();

	scene1->addChild( pencils );
	scene1->addChild( kingkong );

	//World 2
	Scene* scene2 = new Scene();

	Entity* textObj = new Entity();
	textObj->position = Vector2( MINSWIDTH / 2, MINSHEIGHT / 2 );

	Text* text1 = new Text( "MDGFW" );
	text1->setPosition( 50 , 50 );

	textObj->addText( text1 );

	scene1->addChild( textObj );

	SceneManager::addScene( scene1 );
	SceneManager::addScene( scene2 );

	do {
		engine.run( nullptr );

		if ( InputManager::getManager()->getKey( KeyCode::Space ) ) {
			text1->setFont( "fonts/PressStart2P-Regular.ttf" );
		}
		else {
			text1->setFont( DEFAULTFONT );
		}

		float mouseX = InputManager::getManager()->getMouseX();
		float mouseY = InputManager::getManager()->getMouseY();
		text1->setPosition( mouseX, mouseY );

	} // Check if the ESC key was pressed or the window was closed
	while( engine.isRunning() || !glfwWindowShouldClose(engine.getWindow()) == 0 );

	delete scene2;
	delete scene1;//also removes pencils/kingkong and rgba

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
