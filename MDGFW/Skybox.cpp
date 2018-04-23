#include <MDGFW\Skybox.h>

Skybox::Skybox( std::string right_IMGPath, std::string left_IMGPath, std::string top_IMGPath, std::string bottom_IMGPath, std::string front_IMGPath, std::string back_IMGPath ) {
	std::vector<std::string> faces = std::vector<std::string>(6);

	faces[0] = right_IMGPath;
	faces[1] = left_IMGPath;
	faces[2] = top_IMGPath;
	faces[3] = bottom_IMGPath;
	faces[4] = front_IMGPath;
	faces[5] = back_IMGPath;
	
	_texture = ResourceManager::getManager()->getCubeMap( faces );
	_shader = ResourceManager::getManager()->getShader( DEFAULTCUBEMAPSHADERVERTEX, DEFAULTCUBEMAPSHADERFRAGMENT );
	_mesh = new Mesh();

	_shader->setInt( "skybox", 0 );
	_mesh->GenCubeMesh( _texture->getWidth(), _texture->getHeight(), GL_STATIC_DRAW);
}

Skybox::~Skybox() {

}