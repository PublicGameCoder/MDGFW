#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <iostream>

#include <MDGFW\Mesh.h>
#include <MDGFW\ResourceManager.h>

class Sprite
{
	public:
		Sprite(std::string image_path);
		virtual ~Sprite();

		Texture* getTexture() { return _texture; };
		Shader* getShader() { return _shader; };
		Mesh* getMesh() { return _mesh; };

		unsigned int getWidth() { return _width; };
		unsigned int getHeight() { return _height; };

	private:

		Shader* _shader;
		Texture* _texture;
		Mesh* _mesh;

		GLuint _width;
		GLuint _height;
};

#endif /* SPRITE_H */
