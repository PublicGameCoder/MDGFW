#ifndef TEXT_H
#define TEXT_H

#include <MDGFW\UIElement.h>
#include <MDGFW\Mesh.h>

class Text : public UIElement
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

	GLfloat getScale() {
		return _scale;
	}

	std::map<GLchar, Character> getCharacters() {
		return _fontChars;
	}

	GLuint getVAO() {
		return VAO;
	}

	GLuint getVBO() {
		return VBO;
	}

private:
	std::map<GLchar, Character> _fontChars;

	std::string _message;
	RGBAColor _color;

	Shader* _shader;

	float _scale;

	int init();
	void setupShader();

	GLuint VAO, VBO;
};

#endif // !TEXT_H
