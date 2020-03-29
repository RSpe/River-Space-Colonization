#shader vertex
#version 460 core

layout(location = 0) in vec4 position; // Vector value stored as (0, 0, 0, 1) default, send 2 values and the last will remain 0, 1
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

// MVP = model view prjection matrix
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

/* u_ means this is a set uniform variable */
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
	//color = u_Color;
};