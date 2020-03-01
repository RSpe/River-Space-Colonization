#include "Camera.h"

Camera::Camera()
	: cameraPosition(0.0f, 0.0f, 3.0f), cameraTarget(0.0f, 0.0f, 0.0f), cameraFront(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) 
{
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
	Update();
}

Camera::~Camera()
{

}

void Camera::View()
{
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, up);
}

void Camera::ProcessKeyboard(const char* key, double deltaTime)
{
	float velocity = 2.5f * deltaTime;
	if (key == "KEY_W")
		cameraPosition += cameraFront * velocity;
	if (key == "KEY_S")
		cameraPosition -= cameraFront * velocity;
	if (key == "KEY_A")
		cameraPosition -= cameraRight * velocity;
	if (key == "KEY_D")
		cameraPosition += cameraRight * velocity;
}

void Camera::ProcessMouse(double xchange, double ychange)
{

	yaw += xchange;
	pitch += ychange;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Update();
}


void Camera::ProcessScroll(double ychange)
{
	if (fov > 1.0f && fov < 45.0f)
		fov -= ychange;
	else if (fov <= 1.0f)
		fov = 1.0f;
	else if (fov >= 45.0f)
		fov = 45.0f;
}

void Camera::Update()
{
	cameraFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront.y = sin(glm::radians(pitch));
	cameraFront.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));
	cameraFront = glm::normalize(cameraFront);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	up = glm::normalize(glm::cross(cameraRight, cameraFront));
}
