#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <map>

#include "MDGFW\Texture.h"

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager* getManager();
	Texture* getTexture( std::string filePath );
private:
	static ResourceManager* _instance;
	ResourceManager();

	std::map<std::string, Texture*> _textures;
};

#endif // !RESOURCEMANAGER_H
