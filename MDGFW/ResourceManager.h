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

struct Character {
	GLubyte Glyph;
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
	Shader* getShader( std::string vertexPath, std::string fragmentPath );
	FT_Face* getFont( std::string filePath );
	std::map<GLchar, Character*> getFontChars( FT_Face* font );

private:
	FT_Library _freetype;
	int error;

	static ResourceManager* _instance;

	ResourceManager();
	std::map<GLchar, Character*> initFont( FT_Face* font );

	std::map<std::string, Texture*> _textures;
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, FT_Face*> _fonts;
	std::map<FT_Face*, std::map<GLchar, Character*>> _characters;
};

#endif // !RESOURCEMANAGER_H
