#include <MDGFW/camera.h>

glm::mat4 _viewMatrix;

// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );
glm::vec3 cursor = glm::vec3( 0, 0, 0 );

glm::mat4 getViewMatrix(){
	return _viewMatrix;
}

glm::vec3 getCursor(){
	return cursor;
}

float speed = 300.0f; // 300 units / second


void computeMatricesFromInputs(GLFWwindow* window)
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	cursor = glm::vec3( xpos, ypos, 0 );

	// Right and Down vector
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 up = glm::vec3(0, -1, 0);

	// Move up
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += up * Time::deltaTime * speed;
	}
	// Move down
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= up * Time::deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * Time::deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * Time::deltaTime * speed;
	}

	// View matrix
	_viewMatrix = glm::lookAt(
			position, // Camera is at (xpos,ypos,5), in World Space
			position + glm::vec3(0, 0, -5), // and looks towards Z
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
}
