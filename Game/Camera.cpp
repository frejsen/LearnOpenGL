#include "Camera.h"
#include <iostream>
#include <SDL.h>

void Camera::Move(CameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	switch (direction) {
	case CameraMovement::FORWARD:
		Position += velocity * Camera::Front;
		break;
	case CameraMovement::BACKWARD:
		Position -= velocity * Camera::Front;
		break;
	case CameraMovement::LEFT:
		Position -= velocity * Camera::Right;
		break;
	case CameraMovement::RIGHT:
		Position += velocity * Camera::Right;
		break;
	case CameraMovement::UP:
		Position += velocity * Camera::WorldUp;
		break;
	case CameraMovement::DOWN:
		Position -= velocity * Camera::WorldUp;
		break;
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Camera::Front, Camera::WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}