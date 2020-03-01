#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:

	Camera();
	~Camera();

	void View();
	void ProcessKeyboard(const char* key, double deltaTime);
	void ProcessMouse(double xchange, double ychange);
	void ProcessScroll(double ychange);

private:

	void Update();

	double yaw = -90.0f;
	double pitch = 0.0f;
	double fov = 45.0f;

	glm::mat4 view;
	glm::vec3 cameraPosition, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront, up;

};

