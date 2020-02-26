#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormals;

out vec2 texCoord;
out vec3 Normal;
out vec3 toLightVec;
out vec3 toCameraVector;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform vec3 lightPosition;
void main()
{
	vec4 worldPos = transformationMatrix * vec4(aPos,1.0f);
	gl_Position = projectionMatrix * viewMatrix * worldPos;
	texCoord = 40*aTexCoord;
	Normal = (transformationMatrix * vec4(aNormals,0.0)).xyz;
	toLightVec = lightPosition - worldPos.xyz;
	toCameraVector = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPos.xyz;
}