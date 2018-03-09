#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include <MDGFW\Entity.h>

class World : public Entity
{
public:
	World();
	virtual ~World();

	void addSprite( Sprite* sprite ) {
		_sprites.push_back( sprite );
	}

	std::vector<Sprite*> getSprites() {
		return _sprites;
	}

private:
	std::vector<Sprite*> _sprites;
};
#endif // !WORLD_H
