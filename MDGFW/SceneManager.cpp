#include <MDGFW/SceneManager.h>

std::vector<Scene*> SceneManager::_scenes = std::vector<Scene*>();
KeyCode SceneManager::_nextKey = KeyCode::Equal;
KeyCode SceneManager::_prevKey = KeyCode::Minus;

SceneManager::SceneManager() {
	_selected = 0;
}

SceneManager::~SceneManager() {
}

void SceneManager::update() {
	if ( InputManager::getManager()->getKeyDown( _nextKey ) ) {
		int s = _scenes.size() - 1;
		_selected++;
		if ( _selected > s ) {
			_selected = 0;
		}
	}
	else if ( InputManager::getManager()->getKeyDown( _prevKey ) ) {
		_selected--;
		if ( _selected < 0 ) {
			_selected = _scenes.size() - 1;
		}
	}
}