#ifndef CAMERA_H
#define CAMERA_H

#include "pfm/pfm.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.08f;
const float ZOOM        =  45.0f;

class Camera
{
	private:
		void _updateCameraVectors();

	public:
		// camera Attributes
		pfm::vec3 position;
		pfm::vec3 front;
		pfm::vec3 up;
		pfm::vec3 right;
		pfm::vec3 worldUp;
		// euler Angles
		float yaw;
		float pitch;
		// camera options
		float movementSpeed;
		float mouseSensitivity;
		float zoom;

		Camera(pfm::vec3 position = pfm::vec3(0.0f, 0.0f, 0.0f), pfm::vec3 up = pfm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		pfm::mat4 getViewMatrix();

		void processKeyboard(Camera_Movement direction, float deltaTime);
		void processMouseMovement(float xoffset, float yoffset);
};
#endif
