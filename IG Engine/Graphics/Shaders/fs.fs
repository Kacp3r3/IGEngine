#version 440 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normals;
in vec3 toLightVec;


uniform sampler2D texture1;
uniform vec3 lightColor;

void main(void)
{
    vec3 unitNormal = normalize(Normals);
    vec3 unitToLight = normalize(toLightVec);
    float dotvar = dot(unitNormal,unitToLight);
    float brightness = max(dotvar,0.0);
    vec3 diffuse = brightness*lightColor;
    vec4 texColor = vec4(diffuse,1.0)*texture(texture1, texCoord);
    if(texColor.a < 0.8) discard;
    FragColor = texColor;
}