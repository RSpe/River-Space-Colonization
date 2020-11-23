#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * glm::vec4(position[0], 0.0f, position[1], 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

/* u_ means this is a set uniform variable */
uniform vec4 u_Color;

void main()
{
	color = u_Color;
};