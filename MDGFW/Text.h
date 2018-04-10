#ifndef TEXT_H
#define TEXT_H

#include "MDGFW\MDGFWConfig.h"
#include "MDGFW\ResourceManager.h"
#include <MDGFW\VectorX.h>
#include <MDGFW\color.h>

class Text
{
public:
	Text();
	Text(std::string message);

	virtual ~Text();

	void setMessage( std::string message ) {
		_message = message;
	}

	void setFontSize( float size );
	void setFont( std::string path );
	void setColor( RGBAColor color );

	std::string getMessage() {
		return _message;
	}

	RGBAColor getColor() {
		return _color;
	}

	Shader* getShader() {
		return _shader;
	};

	Vector2 getPosition() {
		return _position;
	}

private:
	std::string _message;
	RGBAColor _color;

	Shader* _shader;

	Vector2 _position;
	float _scale;

	int init();
};

#endif // !TEXT_H
