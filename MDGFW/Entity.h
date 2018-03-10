#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\sprite.h>
#include <MDGFW\SHTime.h>

class Entity
{

public:
	Entity();
	virtual ~Entity();
	virtual void update();
	void addSprite(std::string filePath);
	void addChild( Entity* entity );
	void flushSprite();
	Sprite* getSprite();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	std::vector<Entity*> getChilds();
private:
	Sprite* _sprite;

	std::vector<Entity*> _childs;
protected:
};

#endif // !ENTITY_H
