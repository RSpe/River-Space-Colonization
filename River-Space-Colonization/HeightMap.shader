#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertex_colour;

out vec3 fragment_colour;

void main()
{
	gl_Position = position;
	fragment_colour = vertex_colour;
};

#shader fragment
#version 460 core

out vec4 colour;
in vec3 fragment_colour;

void main()
{
	colour = vec4(fragment_colour, 1.0);
};