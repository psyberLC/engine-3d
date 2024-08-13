#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
in vec3 TexCoord;

uniform samplerCube cubemap;
uniform float Time;

void main()
{
	FragColor = texture(cubemap, TexCoord);
}
