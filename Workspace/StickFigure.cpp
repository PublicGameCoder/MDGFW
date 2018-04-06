#include <Workspace\StickFigure.h>

StickFigure::StickFigure() : Entity() {
	this->addSprite( "assets/container.jpg" );
	this->scale = Vector3( 1, 1, 1 );
	
	line = new Line();
	line->setWidth( 5.0f );
	line->setDynamic( true );

	ap = Vector3( MINSWIDTH / 2, MINSHEIGHT / 2, 0.0f ) - position;
	line->setTo( ap, false);

	this->addLine( line );

	tohand = new Line();

	tohand->setWidth( 1.5f );
	tohand->setDynamic( true );

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
	Vector3 mousePos = Vector3( x, y, position.z );
	tohand->setTo( mousePos, true );
}