#include "Camera.h"

Camera::Camera(glm::vec3 start_pos, glm::vec3 start_up, float start_yaw, float start_pitch, float start_move_speed, float start_turn_speed)
{
	position = start_pos;
	world_up = start_up;
	yaw = start_yaw;
	pitch = start_pitch;
	move_speed = start_move_speed;
	turn_speed = start_turn_speed;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	Update();
}

Camera::~Camera()
{

}

glm::mat4 Camera::View()
{
	//std::cout << glm::to_string(position) << std::endl;
	//std::cout << glm::to_string(position + front) << std::endl;
	//std::cout << glm::to_string(up) << std::endl;
	return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(const char* key, double deltaTime)
{
	float velocity = move_speed * deltaTime;
	if (key == "KEY_W")
		position += front * velocity;
	if (key == "KEY_S")
		position -= front * velocity;
	if (key == "KEY_A")
		position -= right * velocity;
	if (key == "KEY_D")
		position += right * velocity;
}

void Camera::ProcessMouse(double xchange, double ychange)
{
	xchange *= turn_speed;
	ychange *= turn_speed;

	yaw += xchange;
	pitch += ychange;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Update();
}


void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw))* cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

glm::vec3 Camera::GetDirection()
{
	return front;
}