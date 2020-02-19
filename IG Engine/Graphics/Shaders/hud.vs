#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;

void main()
{
	vec4 worldPos = transformationMatrix * vec4(aPos,1.0f);
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * worldPos;
	texCoord = aTexCoord;
}