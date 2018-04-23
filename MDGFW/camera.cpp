#include <MDGFW/camera.h>

Camera::Camera() : Entity() {
	position = Vector3( 0, 0, 5 );// Initial position : on +Z
	_cursor = glm::vec3( 0, 0, 0 );
	_speed = 300.0f;

	front = Vector3( 0.0f, 0.0f, -1.0f );
	up = Vector3( 0.0f, 1.0f, 0.0f );
	right = Vector3( 1.0f, 0.0f, 0.0f );

	yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;
	fov = 45.0f;

	float lastX = MINSWIDTH / 2.0;
	float lastY = MINSHEIGHT / 2.0;

	GLFWwindow* window = InputManager::getManager()->getWindow();
	lastX = InputManager::getManager()->getMouseX();
	lastY = InputManager::getManager()->getMouseY();

	if ( USE3D ) {
		perspective();
	}
	else {
		orthographic();
	}
}

Camera::~Camera() {

}

void Camera::orthographic() {
	_projectionMatrix = glm::ortho( 0.0f, ( float ) MINSWIDTH, ( float ) MINSHEIGHT, 0.0f, 0.1f, 100.0f );
}

void Camera::perspective() {
	_projectionMatrix = glm::perspective( glm::radians( fov ), ( float ) MINSWIDTH / ( float ) MINSHEIGHT, 0.1f, 100.0f );
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

	// Move up
	if (InputManager::getManager()->getKey(KeyCode::W ) ){
		position += (up * -1) * Time::deltaTime * _speed;
	}
	// Move down
	if ( InputManager::getManager()->getKey( KeyCode::S ) ){
		position -= (up * -1) * Time::deltaTime * _speed;
	}
	// Strafe right
	if ( InputManager::getManager()->getKey( KeyCode::D ) ){
		position += right * Time::deltaTime * _speed;
	}
	// Strafe left
	if ( InputManager::getManager()->getKey( KeyCode::A ) ) {
		position -= right * Time::deltaTime * _speed;
	}

	if ( InputManager::getManager()->getKey( KeyCode::Right ) ) {
		pitch += 1 * Time::deltaTime;
		std::cout << "New Pitch|Yaw|Roll: " << pitch << " " << yaw << " " << roll << std::endl;
	}

	if ( InputManager::getManager()->getKey( KeyCode::Left ) ) {
		pitch -= 1 * Time::deltaTime;
		std::cout << "New Pitch|Yaw|Roll: " << pitch << " " << yaw << " " << roll << std::endl;
	}

	if ( InputManager::getManager()->getKey( KeyCode::Down ) ) {
		yaw += 1 * Time::deltaTime;
		std::cout << "New Pitch|Yaw|Roll: " << pitch << " " << yaw << " " << roll << std::endl;
	}

	if ( InputManager::getManager()->getKey( KeyCode::Up ) ) {
		yaw -= 1 * Time::deltaTime;
		std::cout << "New Pitch|Yaw|Roll: " << pitch << " " << yaw << " " << roll << std::endl;
	}

	fov += InputManager::getManager()->getScrollVertical( InputManager::getManager()->getWindow() );
	if ( fov <= 1.0f )
		fov = 1.0f;
	if ( fov >= 45.0f )
		fov = 45.0f;

	if ( USE3D ) {
		perspective();
	}
	else {
		orthographic();
	}

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if ( pitch > 89.0f )
		pitch = 89.0f;
	if ( pitch < -89.0f )
		pitch = -89.0f;

	glm::vec3 localFront;
	localFront.x = cos( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
	localFront.y = sin( glm::radians( pitch ) );
	localFront.z = sin( glm::radians( yaw ) ) * cos( glm::radians( pitch ) );
	this->front = glm::normalize( localFront );

	// View matrix
	_viewMatrix = glm::lookAt(
		position.toVec3(), // Camera is at (xpos,ypos,5), in World Space
		position.toVec3() + front.toVec3(), // and looks towards Z
		up.toVec3()  // Head is up (set to 0,-1,0 to look upside-down)
	);
}
