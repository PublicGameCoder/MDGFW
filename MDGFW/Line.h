#ifndef LINE_H
#define LINE_H

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>

class Line
{
public:
	Line();
	~Line();

	void setWidth( float width ) {
		_lineWidth = width;
	}

	void setColor( RGBAColor color ) {
		_color = color;
	}

	void setLocalFrom( Vector3 pos1 ) {
		_pos1 = pos1;
	}

	void setLocalTo( Vector3 pos2 ) {
		_pos2 = pos2;
	}

	float getWidth() {
		return _lineWidth;
	}

	RGBAColor getColor() {
		return _color;
	}

	Vector3 getFrom() {
		return _pos1;
	}
	Vector3 getTo() {
		return _pos2;
	}

private:
	float _lineWidth;
	RGBAColor _color;

	Vector3 _pos1;
	Vector3 _pos2;
};

#endif // !LINE_H
