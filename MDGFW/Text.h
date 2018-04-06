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

	FT_Face* getFont() {
		return _font;
	}

	std::string getFontPath() {
		return _fontPath;
	}

	RGBAColor getColor() {
		return _color;
	}

	GLuint getVBO() {
		return VBO;
	}

	GLuint getVAO() {
		return VAO;
	}

	Shader* getShader() {
		return _shader;
	};

	Vector2 getPosition() {
		return _position;
	}

	Vector2 getScale() {
		return _scale;
	}

private:
	FT_Face* _font;
	std::string _fontPath;
	float _size;
	std::string _message;
	RGBAColor _color;

	Shader* _shader;
	GLuint VAO, VBO;

	Vector2 _position;
	Vector2 _scale;

	int init();
};

#endif // !TEXT_H
