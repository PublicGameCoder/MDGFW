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