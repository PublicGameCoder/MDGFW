#include <MDGFW\Entity.h>

Entity::Entity() {
	position = Vector3();
	scale = Vector3( 1, 1, 1 );
	rotation = Vector3();
	_worldPosition = position;
	_sprite = nullptr;
	_parent = nullptr;
}

Entity::~Entity() {
	for each (Entity* child in _childs)
	{
		if ( child != nullptr ) {
			delete child;
		}
	}

	for each (Line* line in _lines) {
		if ( line != nullptr ) {
			delete line;
		}
	}

	flushSprite();
}

void Entity::update() {
	calcWorldPosition();
}

void Entity::calcWorldPosition() {
	_worldPosition = position;
	if ( _parent == nullptr )return;
	_worldPosition += _parent->_worldPosition;
}

void Entity::addSprite(std::string filePath) {
	flushSprite();
	_sprite = new Sprite( filePath );
}

void Entity::addChild( Entity* entity ) {
	_childs.push_back( entity );
	entity->_parent = this;
	entity->_worldPosition += _worldPosition;
}

void Entity::addLine( Line* line ) {
	_lines.push_back( line );
}

void Entity::addText( Text* text ) {
	_texts.push_back( text );
}

Sprite* Entity::getSprite() {
	return this->_sprite;
}

std::vector<Entity*> Entity::getChilds() {
	return _childs;
}

std::vector<Line*> Entity::getLines() {
	return _lines;
}

std::vector<Text*> Entity::getTexts() {
	return _texts;
}

Vector3 Entity::getWorldPosition() {
	return _worldPosition;
}

void Entity::flushSprite() {
	if ( this->_sprite != NULL ) {
		delete this->_sprite;
	}
}