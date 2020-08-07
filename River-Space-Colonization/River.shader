#shader vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec4 rgba;

out vec4 v_colour;

void main()
{
	gl_Position = position;
	v_colour = rgba;
};

#shader fragment
#version 460 core

out vec4 f_colour;

in vec4 v_colour;

void main()
{
	f_colour = v_colour;
};