#pragma once

#include "Include.h"

class Camera
{
public:

	Camera(glm::vec3 start_pos, glm::vec3 start_up, float start_yaw, float start_pitch, float start_move_speed, float start_turn_speed);
	~Camera();

	glm::mat4 View();
	void ProcessKeyboard(const char* key, double deltaTime);
	void ProcessMouse(double xchange, double ychange);

	glm::vec3 GetPosition();
	glm::vec3 GetDirection();

private:

	void Update();

	float yaw, pitch, move_speed, turn_speed;

	glm::vec3 position, front, up, right, world_up;

};

