#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in mat4 cubeOffset;

out vec3 TexCoord;
out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * cubeOffset * vec4(aPos, 1.0f);
	vertexColor = aColor;
	TexCoord = aPos;
}
