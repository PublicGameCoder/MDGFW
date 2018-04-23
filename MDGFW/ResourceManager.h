#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//Freetype
#include <ft2build.h>
#include FT_FREETYPE_H

//GLM
#include <glm/gtc/type_ptr.hpp>

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
#include <MDGFW\Shader.h>
#include <MDGFW\Mesh.h>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager* getManager();
	Texture* getTexture( std::string filePath );
	Texture* getCubeMap( std::vector<std::string> faces );
	Shader* getShader( std::string vertexPath, std::string fragmentPath );
	std::map<GLchar, Character> getFontChars(std::string fontPath);
private:
	FT_Library _freetype;

	static ResourceManager* _instance;

	ResourceManager();

	std::map<std::string, Texture*> _textures;
	std::map<std::string, Texture*> _cubemaps;
	std::map<std::string, Shader*> _shaders;

	std::map<std::string, std::map<GLchar, Character>> _fontChars;

	std::map<GLchar, Character> loadFont(std::string fontPath);
};

#endif // !RESOURCEMANAGER_H
