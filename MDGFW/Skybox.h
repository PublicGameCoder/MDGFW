#ifndef SKYBOX_H
#define SKYBOX_H

#include <MDGFW\ResourceManager.h>

class Skybox
{
public:
	Skybox( std::string right_IMGPath, std::string left_IMGPath, std::string top_IMGPath, std::string bottom_IMGPath, std::string front_IMGPath, std::string back_IMGPath );
	virtual ~Skybox();

	Texture* getTexture() {
		return _texture;
	};
	Shader* getShader() {
		return _shader;
	};
	Mesh* getMesh() {
		return _mesh;
	};

private:
	Texture* _texture;
	Shader* _shader;
	Mesh* _mesh;
};

#endif // !SKYBOX_H
