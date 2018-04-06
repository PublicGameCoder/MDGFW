#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <MDGFW/Scene.h>

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	static void addScene( Scene* scene ) {
		removeScene( scene );
		_scenes.push_back( scene );
	}

	static void removeScene( Scene* scene ) {
		std::vector<Scene*>::iterator it = std::find( _scenes.begin(), _scenes.end(), scene );
		if ( it != _scenes.end() ) {
			_scenes.erase( it );
		}
	}

	static void setNext( KeyCode nextKey ) {
		_nextKey = nextKey;
	}

	static void setPrev( KeyCode prevKey ) {
		_prevKey = prevKey;
	}

	Scene* getCurrent() {
		return _scenes[_selected];
	}

	void update();

private:
	int _selected;
	static std::vector<Scene*> _scenes;

	static KeyCode _nextKey;
	static KeyCode _prevKey;
};

#endif // !SCENEMANAGER_H
