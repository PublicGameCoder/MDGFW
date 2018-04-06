#include "MDGFW/ResourceManager.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager* ResourceManager::getManager() {
	if ( !_instance ) {
		_instance = new ResourceManager();
	}
	return _instance;
}

ResourceManager::ResourceManager() {
	error = FT_Init_FreeType( &_freetype );
	if ( error ) {
		printf( "Error occurred when initializing FreeType library!\n" );
	}
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
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

	for each (std::pair<const std::string, FT_Face*> set in _fonts) {
		FT_Face* face = set.second;
		if ( face != nullptr ) {
			FT_Done_Face( *face );
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
		Texture* t = new Texture(filePath);
		if ( t != nullptr && t != NULL ) {
			_textures[filePath] = t;
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

FT_Face* ResourceManager::getFont( std::string filePath ) {
	std::cout << "Loading Font: " << filePath.c_str() << std::endl;
	if ( _fonts[filePath] != nullptr ) {
		std::cout << "Font: '" << filePath.c_str() << "' is already loaded!" << std::endl;
		return _fonts[filePath];
	}
	else {
		FT_Face* face = new FT_Face();
		error = FT_New_Face( _freetype, "fonts/arial.ttf", 0, face );
		if ( error == FT_Err_Unknown_File_Format ) {
			std::cout << "Font format is unsupported" << std::endl;
		}
		else if ( error ) {
			std::cout << "Font file is missing or corrupted" << std::endl;
		}
		else {
			std::cout << "Font: "<< filePath <<" is sucessfully loaded!" << std::endl;
		}
		if ( face != nullptr && face != NULL ) {
			_fonts[filePath] = face;
		}
		return face;
	}
}

std::map<GLchar, Character*> ResourceManager::getFontChars( FT_Face* font ) {
	std::map<FT_Face*, std::map<GLchar, Character*>>::iterator it = _characters.find(font);
	if (it != _characters.end() ) {
		return it->second;
	}
	else {
		return initFont(font);
	}
}

std::map<GLchar, Character*> ResourceManager::initFont( FT_Face* font ) {
	std::map<GLchar, Character*> fontCharacters;
	// Load first 128 characters of ASCII set
	for ( GLubyte c = 0; c < 128; c++ )
	{
		// Load character glyph 
		if ( FT_Load_Char( (*font), c, FT_LOAD_RENDER ) )
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
			(*font)->glyph->bitmap.width,
			(*font)->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			(*font)->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		// Now store character for later use
		Character character = {
			c,
			texture,
			glm::ivec2( (*font)->glyph->bitmap.width, (*font)->glyph->bitmap.rows ),
			glm::ivec2( (*font)->glyph->bitmap_left, (*font)->glyph->bitmap_top ),
			(*font)->glyph->advance.x
		};
		Character* _char;
		_char = &character;
		fontCharacters.insert( std::pair<GLchar, Character*>( c, _char ) );
	}
	_characters.insert( std::pair<FT_Face*, std::map<GLchar, Character*>>( font, fontCharacters ) );

	return fontCharacters;
}