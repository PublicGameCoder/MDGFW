#ifndef LINE_H
#define LINE_H

#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>

class Line
{
public:
	Line();
	~Line();

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
