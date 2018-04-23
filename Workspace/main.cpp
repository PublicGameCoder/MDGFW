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

	Entity* cube = new Entity();

	Entity* textObj = new Entity();
	textObj->position = Vector2( MINSWIDTH / 2, MINSHEIGHT / 2 );

	Text* text1 = new Text( "MDGFW" );
	text1->setPosition( 50, 50 );

	textObj->addText( text1 );

	scene1->addChild( textObj );

	//World 2
	Scene* scene2 = new Scene();

	Text* text2 = new Text();
	text2->setMessage( "TEST" );
	text2->setPosition(200,200);

	Entity* TextObject2 = new Entity();
	TextObject2->position = Vector2( MINSWIDTH / 2, MINSHEIGHT / 2 );
	TextObject2->addText( text2 );
	scene2->addChild( TextObject2 );

	scene1->addSkybox( "skyboxes/mp_alpha/alpha-island_rt.png" , "skyboxes/mp_alpha/alpha-island_lf.png" , "skyboxes/mp_alpha/alpha-island_up.png" , "skyboxes/mp_alpha/alpha-island_dn.png" , "skyboxes/mp_alpha/alpha-island_ft.png" , "skyboxes/mp_alpha/alpha-island_bk.png" );

	SceneManager::addScene( scene1 );
	SceneManager::addScene( scene2 );

	SceneManager::setNext( KeyCode::RightBracket );
	SceneManager::setPrev( KeyCode::LeftBracket );

	float time = 1.0f;
	int index = 0;
	do {
		engine.run( nullptr );

		if ( InputManager::getManager()->getKey( KeyCode::Space ) ) {
			text1->setFont( "fonts/PressStart2P-Regular.ttf" );
			text2->setFont( "fonts/PressStart2P-Regular.ttf" );
		}
		else {
			text1->setFont( DEFAULTFONT );
			text2->setFont( DEFAULTFONT );
		}

		float mouseX = InputManager::getManager()->getMouseX();
		float mouseY = InputManager::getManager()->getMouseY();
		text1->setPosition( mouseX, mouseY );
		text2->setPosition( mouseX, mouseY );

		//Make text change the message and color each second
		time -= Time::deltaTime;
		if ( time <= 0.0f ) {
			time = 1.0f;
			index++;
			if ( index > 3 ) {
				index = 0;
			}
		}
		switch ( index ) {
		case 0:
			text2->setMessage( "TEST" );
			text2->setColor( WHITE );
			break;
		case 1:
			text2->setMessage( "TEST1" );
			text2->setColor( BLUE );
			break;
		case 2:
			text2->setMessage( "TEST12" );
			text2->setColor( GREEN );
			break;
		case 3:
			text2->setMessage( "TEST123" );
			text2->setColor( RED );
			break;
		default:
			text2->setMessage( "TEST" );
			text2->setColor( WHITE );
			break;
		}

		if ( InputManager::getManager()->getKey(KeyCode::Space) ) {
			TextObject2->getAnimator()->Play();
		}

	} // Check if the ESC key was pressed or the window was closed
	while( engine.isRunning() || !glfwWindowShouldClose(engine.getWindow()) == 0 );

	delete scene2;
	delete scene1;//also removes pencils/kingkong and rgba

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
