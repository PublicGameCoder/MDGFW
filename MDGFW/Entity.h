#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\Line.h>
#include <MDGFW\Text.h>
#include <MDGFW\sprite.h>
#include <MDGFW\Animator.h>
#include <MDGFW\InputManager.h>
#include <MDGFW\MDGTime.h>
#include <MDGFW\Mathmatics.h>

class Entity
{

public:
	Entity();
	virtual ~Entity();
	virtual void Update() = 0;
	void addSprite(std::string filePath);
	void addChild( Entity* entity );
	void addLine( Line* line );
	void addText( Text* text );
	void flushSprite();
	Sprite* getSprite();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	std::vector<Entity*> getChilds();
	std::vector<Line*> getLines();
	std::vector<Text*> getTexts();
	Vector3 getWorldPosition();
	Animator* getAnimator();
private:
	Animator* _animator;
	Entity* _parent;
	Vector3 _worldPosition;
	Sprite* _sprite;

	std::vector<Entity*> _childs;
	std::vector<Line*> _lines;
	std::vector<Text*> _texts;

	void calcWorldPosition();
protected:
};

#endif // !ENTITY_H
