#ifndef LINE_H
#define LINE_H

#include <gl/glew.h>

#include <vector>
#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>
#include <ResourceManager.h>

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

	Shader* getShader() {
		return _shader;
	};

	const std::vector<Vector3> getAnchors() {
		return _anchorPoints;
	}

	bool isFromLocal() {
		return _isFromLocal;
	}

	bool isToLocal() {
		return _isToLocal;
	}

	void recalculate( Vector3 worldPos );

	GLuint getVBO() {
		return _vbo;
	}

	GLuint getUVBO() {
		return _uvbo;
	}

	bool isDynamic() {
		return _dynamic;
	}

	void setDynamic( bool state ) {
		_dynamic = state;
	}

private:
	Shader* _shader;
	GLuint _vbo;
	GLuint _uvbo;

	float _lineWidth;
	RGBAColor _color;

	Vector3 _pos1;
	Vector3 _pos2;

	bool _isFromLocal;
	bool _isToLocal;

	bool _dynamic;

	std::vector<Vector3> _anchorPoints;
};

#endif // !LINE_H
