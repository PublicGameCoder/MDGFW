#ifndef TEXT_H
#define TEXT_H

#include "MDGFW\ResourceManager.h"

class Text
{
public:
	Text();
	~Text();

	GLuint vertexbuffer() {
		return _vertexbuffer;
	};
	GLuint uvbuffer() {
		return _uvbuffer;
	};

private:
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
};

#endif // !TEXT_H
