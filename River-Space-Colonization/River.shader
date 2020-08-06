#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec4 rgba;

void main()
{
	gl_Position = position;
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

/* u_ means this is a set uniform variable */
//uniform vec4 u_Color;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};