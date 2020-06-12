#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 translated = vec4(aPos,1.f);
	translated.x *= 1800.f;
	translated.y *= 1800.f;
	translated.z *= 1800.f;
	translated += vec4(800.f,0.f,800.f,0.f);
	gl_Position = projectionMatrix*viewMatrix * translated;
	TexCoords = aPos;
}