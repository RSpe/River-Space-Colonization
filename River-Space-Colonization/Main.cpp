#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "TestTreeSpaceColonisation.h"

void process_input(GLFWwindow* window);
void process_mouse(GLFWwindow* window, double x_pos, double y_pos);

const unsigned int window_width = 600;
const unsigned int window_height = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), 90.0f, 0.0f, 20.0f, 0.5f);

float delta_time = 0.0f;
float last_frame = 0.0f;
float last_x = window_width / 2.0f;
float last_y = window_height / 2.0f;
bool first_mouse = true;

int main(void) 
{
	GLFWwindow* window;

	if (!glfwInit()) 
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	 
	/* Create window mode and its OpenGL context */
	window = glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's current context */
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, process_mouse);
	glfwSwapInterval(1);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	else
	{
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));
		GLCall(glDisable(GL_BLEND));

		Renderer renderer;

		TestTreeSpaceColonisation generation;

		glm::mat4 perspective_projection = glm::perspective(45.0f, (float)window_width / window_height, 0.1f, 100.0f);

		while (!glfwWindowShouldClose(window))
		{
			float current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			last_frame = current_frame;

			process_input(window);

			glm::mat4 view = camera.View();
			//std::cout << glm::to_string(view[0]) << std::endl;
			//glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(500.0f, 0, 0));

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
			
			generation.OnRender(perspective_projection, view, model);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
		return 0;
	}
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard("KEY_W", delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard("KEY_S", delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard("KEY_A", delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard("KEY_D", delta_time);
}

void process_mouse(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	float xoffset = x_pos - last_x;
	float yoffset = last_y - y_pos; // reversed since y-coordinates go from bottom to top

	last_x = x_pos;
	last_y = y_pos;

	camera.ProcessMouse(xoffset, yoffset);
}