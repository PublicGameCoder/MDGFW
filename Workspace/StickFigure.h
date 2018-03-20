#ifndef STICKFIGURE_H
#define STICKFIGURE_H

#include <MDGFW\Entity.h>

class StickFigure : public Entity 
{
public:
	StickFigure();
	virtual ~StickFigure();
	void update();
private:
	float speed;
	Line* line, *tohand;
	Vector3 ap;
};
#endif // !STICKFIGURE_H
