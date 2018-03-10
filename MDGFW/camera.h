#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <MDGFW\Entity.h>
#include <MDGFW\SHTime.h>

class Camera : public Entity
{
public:
	Camera();
	virtual ~Camera();

	void updateCamera( GLFWwindow* window );
	glm::mat4 getViewMatrix();
	glm::vec3 getCursor();

private:
	glm::mat4 _viewMatrix;

	glm::vec3 _cursor;

	float _speed; // 300 units / second
};

#endif
