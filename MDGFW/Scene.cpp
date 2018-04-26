#include <MDGFW\Scene.h>

Scene::Scene() : Entity() {
	_skybox = nullptr;
}

Scene::~Scene() {
	deleteSkybox();
}

void Scene::Update() {

}

void Scene::addSkybox( std::string right_IMGPath, std::string left_IMGPath, std::string top_IMGPath, std::string bottom_IMGPath, std::string front_IMGPath, std::string back_IMGPath ) {
	deleteSkybox();
	_skybox = new Skybox( right_IMGPath, left_IMGPath, top_IMGPath, bottom_IMGPath, front_IMGPath, back_IMGPath );
}