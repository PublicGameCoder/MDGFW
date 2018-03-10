#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\Line.h>
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
	void addLine( Line* line );
	void flushSprite();
	Sprite* getSprite();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	std::vector<Entity*> getChilds();
	std::vector<Line*> getLines();
	Vector3 getWorldPosition();
private:
	Entity* _parent;
	Vector3 _worldPosition;
	Sprite* _sprite;

	std::vector<Entity*> _childs;
	std::vector<Line*> _lines;

	void calcWorldPosition();
protected:
};

#endif // !ENTITY_H
