#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormals;

out vec2 texCoord;
out vec3 Normals;
out vec3 toLightVec;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform vec3 lightPosition;

void main()
{
	vec4 worldPos = transformationMatrix * vec4(aPos,1.0f);
	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * worldPos;
	texCoord = aTexCoord;
	Normals = (transformationMatrix * vec4(aNormals,1.0)).xyz;
	toLightVec = lightPosition - worldPos.xyz;
}