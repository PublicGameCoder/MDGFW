#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <MDGFW\Entity.h>
#include <MDGFW\Skybox.h>

class Scene : public Entity
{
public:
	Scene();
	virtual ~Scene();
	void Update();

	void addSkybox( std::string right_IMGPath, std::string left_IMGPath, std::string top_IMGPath, std::string bottom_IMGPath, std::string front_IMGPath, std::string back_IMGPath );
	
	void deleteSkybox() {
		if ( _skybox != nullptr ) {
			delete _skybox;
		}
	};
	Skybox* getSkybox() {
		return _skybox;
	};

private:
	Skybox* _skybox;
};
#endif // !WORLD_H
