#ifndef CANVAS_H
#define CANVAS_H

#include <MDGFW\UIElement.h>

class Canvas
{
public:
	Canvas();
	virtual ~Canvas();

private:
	Vector3 _position;
};

#endif // !CANVAS_H