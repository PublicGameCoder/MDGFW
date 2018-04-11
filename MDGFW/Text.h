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

	GLfloat getScale() {
		return _scale;
	}

	GLuint getVAO() {
		return VAO;
	}

	GLuint getVBO() {
		return VBO;
	}

	std::map<GLchar, Character> getCharacters() {
		return _fontChars;
	}

	void setPosition( float x, float y ) {
		setPosition( Vector2( x, y ) );
	}

	void setPosition( Vector2 position ) {
		this->_position = position;
	}

private:
	std::map<GLchar, Character> _fontChars;
	GLuint VAO, VBO;

	std::string _message;
	RGBAColor _color;

	Shader* _shader;

	Vector2 _position;
	float _scale;

	int init();
	void setupShader();
	void generateQuad();
};

#endif // !TEXT_H
