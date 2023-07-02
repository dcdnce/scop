#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->movementSpeed = SPEED;
	this->mouseSensitivity = SENSITIVITY;
	this->zoom = ZOOM;
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	_updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::_updateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(direction);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	//  when pitch  out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	_updateCameraVectors();
}
