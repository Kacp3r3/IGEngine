#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 scaled = vec4(aPos,1.0);
	scaled.x *= 500.f;
	scaled.y *= 500.f;
	scaled.z *= 500.f;
	gl_Position = projectionMatrix*viewMatrix * scaled;
	TexCoords = aPos;
}