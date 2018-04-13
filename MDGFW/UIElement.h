#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "MDGFW\MDGFWConfig.h"
#include "MDGFW\ResourceManager.h"
#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>

enum Pivot {
	BOTTOMLEFT,
	CENTER
};

class UIElement
{
public:
	UIElement();
	~UIElement();

	void setPosition( Vector2 canvasPosition ) {
		_canvasPosition = canvasPosition;
	}
	void setPosition( float x, float y ) {
		setPosition( Vector2( x, y ) );
	}
	Vector2 getCanvasPosition() {
		return _canvasPosition;
	}

private:
	Vector2 _canvasPosition;
};

#endif // !UIELEMENT_H
