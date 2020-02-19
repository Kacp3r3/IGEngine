#version 440 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;

void main(void)
{
    vec4 texColor = texture(texture1, texCoord);
    if(texColor.a < 0.8) discard;
    FragColor = texColor;
}