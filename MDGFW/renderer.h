#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <fstream>

#include <MDGFW\Mathmatics.h>
#include <MDGFW/camera.h>
#include <MDGFW/Line.h>
#include <MDGFW/sprite.h>
#include <MDGFW/World.h>

class Renderer
{
	public:
		Renderer();
		virtual ~Renderer();
		void updateWorld( World* world );

		GLFWwindow* window() { return _window; };

		unsigned int width() { return _window_width; };
		unsigned int height() { return _window_height; };

		void useVSYNC(bool state) {
			glfwSwapInterval( state );
		}

	private:

		Camera* _camera;

		int init();

		GLFWwindow* _window;
		unsigned int _window_width;
		unsigned int _window_height;

		GLuint loadShaders(
			const char* vertex_file_path,
			const char* fragment_file_path
		);

		void renderLines( Entity* entity );
		void updateEntity( Entity* entity );

		void renderSprite( Sprite* sprite, Vector3 pos, Vector3 scl, Vector3 rot );
		void renderSprite( Sprite* sprite, float px, float py, float sx, float sy, float rot );

		GLuint _programID;

		glm::mat4 _projectionMatrix;

		Vector3& toWorldSpace( Entity* owner, Vector3 pos, bool isLocal );
};

#endif /* RENDERER_H */
