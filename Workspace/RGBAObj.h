#ifndef RGBAOBJ_H
#define RGBAOBJ_H

#include <MDGFW\Entity.h>

class RGBAObj : public Entity {
public:
	RGBAObj();
	virtual ~RGBAObj();
	virtual void update();
private:

};

RGBAObj::RGBAObj() {
}

RGBAObj::~RGBAObj() {
}

void RGBAObj::update() {
	this->rotation.z += (0.3f * Time::deltaTime);
}

#endif // !RGBAOBJ_H
