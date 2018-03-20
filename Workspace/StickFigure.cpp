#include <Workspace\StickFigure.h>

StickFigure::StickFigure() : Entity() {
	this->addSprite( "assets/pencils.tga" );
	
	line = new Line();
	line->setWidth( 5.0f );
	line->setPrecision( 12 );

	ap = Vector3( MINSWIDTH / 2, MINSHEIGHT / 2, 0.0f ) - position;
	line->setTo( ap, false);

	this->addLine( line );

	tohand = new Line();

	tohand->setWidth( 1.5f );
	tohand->setPrecision( 12 );

	this->addLine( tohand );

	speed = 300.0f;
}

StickFigure::~StickFigure() {

}

void StickFigure::update() {
	if ( InputManager::getManager()->getKey( KeyCode::A ) ) {
		this->position.x -= Time::deltaTime * speed;
	}

	if ( InputManager::getManager()->getKey( KeyCode::D ) ) {
		this->position.x += Time::deltaTime * speed;
	}

	if ( InputManager::getManager()->getKey( KeyCode::S ) ) {
		this->position.y += Time::deltaTime * speed;
	}

	if ( InputManager::getManager()->getKey( KeyCode::W ) ) {
		this->position.y -= Time::deltaTime * speed;
	}

	double x = InputManager::getManager()->getMouseX() - position.x;
	double y = InputManager::getManager()->getMouseY() - position.y;
	Vector3 mousePos = Vector3( x, y );
	tohand->setTo( mousePos, false);

	if ( InputManager::getManager()->getMouse( 0 ) ) {
		line->setTo( mousePos, false );
		//line->addLocalAnchorPoint( mousePos );
	}
}