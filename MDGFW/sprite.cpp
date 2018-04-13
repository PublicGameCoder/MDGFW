#include <MDGFW/sprite.h>

Sprite::Sprite(std::string image_path)
{

	// Load image as texture
	_texture = ResourceManager::getManager()->getTexture(image_path);
	_shader = ResourceManager::getManager()->getShader( DEFAULTMESHSHADERVERTEX, DEFAULTMESHSHADERFRAGMENT );
	_mesh = new Mesh();

	_mesh->GenQuadMesh( _texture->getWidth(), _texture->getHeight(), GL_STATIC_DRAW);
}

Sprite::~Sprite()
{

}
