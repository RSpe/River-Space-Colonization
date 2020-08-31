#shader vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 rgba;

out vec4 v_colour;

void main()
{
	gl_Position = position;
	v_colour = rgba;
};

#shader fragment
#version 460 core

in vec4 v_colour;

layout (location = 0) out vec4 f_colour;

void main()
{
	f_colour = v_colour;
};