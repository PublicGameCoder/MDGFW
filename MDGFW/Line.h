#ifndef LINE_H
#define LINE_H

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>

class Entity;

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

	void setFrom( Vector3 pos1, bool global) {
		_pos1 = pos1;
		_isFromLocal = !global;
	}

	void setTo( Vector3 pos2, bool global ) {
		_pos2 = pos2;
		_isToLocal = !global;
	}

	void setParent( Entity* parent ) {
		_parent = parent;
	}

	//A line can have up to 9 anchor points.
	void addLocalAnchorPoint( Vector3 ap ) {
		_anchorPoints.push_back( ap );
	}

	bool hasAnchors() {
		return (_anchorPoints.size() > 0);
	}

	void flushAnchors() {
		_anchorPoints = std::vector<Vector3>();
	}

	void setPrecision(int precision) {
		if ( precision < 2 ) {
			precision = 2;
		}
		_precision = precision;
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

	std::vector<Vector3> getAnchors() {
		return _anchorPoints;
	}

	int getPrecision() {
		return _precision;
	}

	bool isFromLocal() {
		return _isFromLocal;
	}

	bool isToLocal() {
		return _isToLocal;
	}

private:
	float _lineWidth;
	RGBAColor _color;

	Vector3 _pos1;
	Vector3 _pos2;

	bool _isFromLocal;
	bool _isToLocal;

	int _precision;

	std::vector<Vector3> _anchorPoints;

	Entity* _parent;
};

#endif // !LINE_H
