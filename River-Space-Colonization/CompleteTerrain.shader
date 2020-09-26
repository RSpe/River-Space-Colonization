#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 rgba;
layout(location = 2) in vec3 normal;

out vec4 v_colour;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * glm::vec4(position, 1.0f);
	v_colour = glm::vec4(rgba, 1.0f);
	//v_colour = glm::vec4(rgba, 1.0f);
};

#shader fragment
#version 460 core

in vec4 v_colour;

layout(location = 0) out vec4 f_colour;

void main()
{
	f_colour = v_colour;
};