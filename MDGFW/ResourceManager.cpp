#include "MDGFW/ResourceManager.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager* ResourceManager::getManager() {
	if ( !_instance ) {
		_instance = new ResourceManager();
	}
	return _instance;
}

ResourceManager::ResourceManager() {
	if ( FT_Init_FreeType( &_freetype ) ) {
		printf( "Error occurred when initializing FreeType library!\n" );
	}
} 

ResourceManager::~ResourceManager() {
	for each (std::pair<const std::string, Shader*> set in _shaders) {
		Shader* shader = set.second;
		if ( shader != nullptr ) {
			delete shader;
		}
	}

	for each (std::pair<const std::string, Texture*> set in _textures) {
		Texture* texture = set.second;
		if ( texture != nullptr ) {
			delete texture;
		}
	}

	for each (std::pair<const std::string, Texture*> set in _cubemaps) {
		Texture* texture = set.second;
		if ( texture != nullptr ) {
			delete texture;
		}
	}

	FT_Done_FreeType( _freetype );
}

Texture* ResourceManager::getTexture( std::string filePath ) {
	std::cout << "Loading Texture: " << filePath.c_str() << std::endl;
	if ( _textures[filePath] != nullptr) {
		std::cout << "Texture: '" << filePath.c_str() << "' is already loaded!" << std::endl;
		return _textures[filePath];
	}
	else {
		Texture* t = new Texture();
		t->load2DTexture( filePath );
		if ( t != nullptr && t != NULL ) {
			_textures[filePath] = t;
		}
		return t;
	}
}

Texture* ResourceManager::getCubeMap( std::vector<std::string> faces ) {
	std::string def = "";
	for ( std::string face : faces ) {
		def += face + ":";
	}
	std::cout << "Loading Cubemap: " << faces[0].c_str() << " & " << faces[1].c_str() << " & " << faces[2].c_str() << " & " << faces[3].c_str() << " & " << faces[4].c_str() << " & " << faces[5].c_str() << std::endl;
	if ( _cubemaps[def] != nullptr ) {
		std::cout << "Cubemap: '" << faces[0].c_str() << " & " << faces[1].c_str() << " & " << faces[2].c_str() << " & " << faces[3].c_str() << " & " << faces[4].c_str() << " & " << faces[5].c_str() << "' is already loaded!" << std::endl;
		return _cubemaps[def];
	}
	else {
		Texture* t = new Texture();
		t->loadSkybox( faces );
		if ( t != nullptr && t != NULL ) {
			_cubemaps[def] = t;
		}
		return t;
	}
}

Shader* ResourceManager::getShader( std::string vertexPath, std::string fragmentPath ) {
	std::cout << "Loading Shader: vertex('" << vertexPath.c_str() << "') fragment('" << fragmentPath.c_str() << "')" << std::endl;
	std::string combinedName = vertexPath + fragmentPath;
	if ( _shaders[combinedName] != nullptr ) {
		std::cout << "Shader: vertex('" << vertexPath.c_str() << "') fragment('" << fragmentPath.c_str() << "') is already loaded!" << std::endl;
		return _shaders[combinedName];
	}
	else {
		Shader* shader = new Shader( vertexPath.c_str(), fragmentPath.c_str() );
		if ( shader != nullptr && shader != NULL ) {
			_shaders[combinedName] = shader;
		}
		return shader;
	}
}

std::map<GLchar, Character> ResourceManager::getFontChars( std::string fontPath ) {
	std::map<std::string, std::map<GLchar, Character>>::iterator it = _fontChars.find( fontPath );
	std::map<GLchar, Character> characters;
	if ( it == _fontChars.end() ) {
		characters = loadFont( fontPath );
	}
	else {
		characters = it->second;
	}
	return characters;
}

std::map<GLchar, Character> ResourceManager::loadFont( std::string fontPath ) {

	std::cout << "Loading Font: " << fontPath << std::endl;

	// Load font as face
	FT_Face face;
	if ( FT_New_Face( _freetype, fontPath.c_str(), 0, &face ) ) {
		std::cout << "Failed to load font: " << fontPath << std::endl;
		std::cout << "Switched over to default font: " << DEFAULTFONT << std::endl;
		return getFontChars(DEFAULTFONT);//Return default font when requested font couldn't be loaded.
	}

	std::cout << "Generating Font: " << fontPath << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes( face, 0, 48 );

	// Disable byte-alignment restriction
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	std::map<GLchar, Character> pair;
	// Load first 128 characters of ASCII set
	for ( GLubyte c = 0; c < 128; c++ )
	{
		// Load character glyph 
		if ( FT_Load_Char( face, c, FT_LOAD_RENDER ) )
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures( 1, &texture );
		glBindTexture( GL_TEXTURE_2D, texture );
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2( face->glyph->bitmap.width, face->glyph->bitmap.rows ),
			glm::ivec2( face->glyph->bitmap_left, face->glyph->bitmap_top ),
			face->glyph->advance.x
		};
		pair.insert( std::pair<GLchar, Character>( c, character ) );
	}

	_fontChars.insert( std::pair<std::string, std::map<GLchar, Character>>( fontPath, pair ) );

	glBindTexture( GL_TEXTURE_2D, 0 );
	// Destroy FreeType once we're finished
	FT_Done_Face( face );

	std::cout << "successfully generated Font: " << fontPath << std::endl;

	return pair;
}