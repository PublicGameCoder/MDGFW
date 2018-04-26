#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include <MDGFW\Entity.h>

class Camera : public Entity
{
public:
	Camera();
	virtual ~Camera();
	void Update();

	void updateCamera( GLFWwindow* window );
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	glm::vec3 getCursor();

private:
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::vec3 _cursor;

	float _speed; // 300 units / second

	float _nearPlane, _farPlane;
	
	Vector3 front;
	Vector3 up;
	Vector3 right;

	float yaw;
	float pitch;
	float roll;
	float lastX;
	float lastY;
	float fov;

	
	void orthographic();
	void perspective();
};

#endif
