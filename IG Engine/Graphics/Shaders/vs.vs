#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoord;

out vec3 color;
uniform mat4 transformation;
//uniform mat4 model;
void main()
{
	//gl_Position = model*vec4(aPos, 1.0f);
	color = aPos;
	gl_Position = transformation*vec4(aPos,1.0f);
	//TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}