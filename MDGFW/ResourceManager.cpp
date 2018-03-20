#include "MDGFW\ResourceManager.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager* ResourceManager::getManager() {
	if ( !_instance ) {
		_instance = new ResourceManager();
	}
	return _instance;
}

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {

}

Texture* ResourceManager::getTexture( std::string filePath ) {
	if ( _textures[filePath] != nullptr) {
		std::cout << "Image: '" << filePath.c_str() << "' is already loaded!" << std::endl;
		return _textures[filePath];
	}
	else {
		Texture* t = new Texture(filePath);
		_textures[filePath] = t;
		return t;
	}
}