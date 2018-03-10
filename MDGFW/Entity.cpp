#include <MDGFW\Entity.h>

Entity::Entity() {
	_sprite = nullptr;
}

Entity::~Entity() {
	for each (Entity* child in _childs)
	{
		if ( child != nullptr ) {
			delete child;
		}
	}
	flushSprite();
}

void Entity::update() {

}

void Entity::addSprite(std::string filePath) {
	flushSprite();
	_sprite = new Sprite( filePath );
}

void Entity::addChild( Entity* entity ) {
	_childs.push_back( entity );
}

Sprite* Entity::getSprite() {
	return this->_sprite;
}

std::vector<Entity*> Entity::getChilds() {
	return _childs;
};

void Entity::flushSprite() {
	if ( _sprite != nullptr ) {
		delete _sprite;
	}
}