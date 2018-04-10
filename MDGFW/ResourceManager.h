#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

//Glew
#include <GL/glew.h>

//STD
#include <iostream>
#include <string>
#include <map>

//My Own
#include <MDGFW\MDGFWConfig.h>
#include "MDGFW\Texture.h"
#include <MDGFW\VectorX.h>
#include <Shader.h>

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager* getManager();
	Texture* getTexture( std::string filePath );
	Shader* getShader( std::string vertexPath, std::string fragmentPath );

private:
	FT_Library _freetype;
	int error;

	static ResourceManager* _instance;

	ResourceManager();

	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
};

#endif // !RESOURCEMANAGER_H
