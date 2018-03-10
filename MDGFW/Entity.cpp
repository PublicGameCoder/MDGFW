#include <MDGFW\Entity.h>

Entity::Entity() {
	position = Vector3();
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

Sprite* Entity::getSprite() {
	return this->_sprite;
}

std::vector<Entity*> Entity::getChilds() {
	return _childs;
}

std::vector<Line*> Entity::getLines() {
	return _lines;
}

Vector3 Entity::getWorldPosition() {
	return _worldPosition;
}

void Entity::flushSprite() {
	if ( _sprite != nullptr ) {
		delete _sprite;
	}
}