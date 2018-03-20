#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <map>

class ResourceManager;

class Texture
{
public:
	Texture(const std::string &filePath);
	~Texture();

	GLuint getID() {
		return _textureID;
	}

	int getWidth() {
		return _width;
	}

	int getHeight() {
		return _height;
	}

	int getChannels() {
		return _nrChannels;
	}

private:
	GLuint _textureID;
	int _nrChannels;
	int _width;
	int _height;

	void getIDFromData( const std::string &filePath );
};

#endif // !TEXTURE_H
