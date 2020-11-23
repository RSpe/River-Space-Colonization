#shader vertex
#version 460 core

layout(location = 0) in vec2 position;

void main()
{
	gl_Position = glm::vec4(position, 0.0f, 1.0f);
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