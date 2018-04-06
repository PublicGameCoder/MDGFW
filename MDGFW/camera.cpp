#include <MDGFW/camera.h>

Camera::Camera() : Entity() {
	position = Vector3( 0, 0, 5 );// Initial position : on +Z
	_cursor = glm::vec3( 0, 0, 0 );
	_speed = 300.0f;

	orthographic();
}

Camera::~Camera() {

}

void Camera::orthographic() {
	_projectionMatrix = glm::ortho( 0.0f, ( float ) MINSWIDTH, ( float ) MINSHEIGHT, 0.0f, 0.1f, 100.0f );
}

glm::mat4 Camera::getViewMatrix(){
	return _viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return _projectionMatrix;
}

glm::vec3 Camera::getCursor(){
	return _cursor;
}


void Camera::updateCamera(GLFWwindow* window) {
	// Right and Down vector
	Vector3 right = Vector3( 1, 0, 0 );
	Vector3 up = Vector3( 0, -1, 0 );

	// Move up
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += up * Time::deltaTime * _speed;
	}
	// Move down
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= up * Time::deltaTime * _speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * Time::deltaTime * _speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * Time::deltaTime * _speed;
	}

	glm::vec3 _direction = glm::vec3( 0, 0, -5 );

	glm::vec3 _up = glm::vec3( 0, 1, 0 );

	// View matrix
	_viewMatrix = glm::lookAt(
		position.toVec3(), // Camera is at (xpos,ypos,5), in World Space
		position.toVec3() + _direction, // and looks towards Z
		_up  // Head is up (set to 0,-1,0 to look upside-down)
	);
}
