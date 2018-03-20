#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <iostream>

#include "MDGFW\ResourceManager.h"

class Sprite
{
	public:
		Sprite(std::string image_path);
		virtual ~Sprite();

		Texture* texture() { return _texture; };
		GLuint vertexbuffer() { return _vertexbuffer; };
		GLuint uvbuffer() { return _uvbuffer; };

		unsigned int width() { return _width; };
		unsigned int height() { return _height; };

	private:

		Texture* _texture;
		GLuint _vertexbuffer;
		GLuint _uvbuffer;

		unsigned int _width;
		unsigned int _height;
};

#endif /* SPRITE_H */
