#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;
uniform mat4 model;
void main()
{
	color = vec3(1.f,0.f,0.f);
	gl_Position = model*vec4(aPos,1.0f);
	texCoord = aTexCoord;
}