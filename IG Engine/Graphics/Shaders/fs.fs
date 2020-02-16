#version 440 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 color;
uniform sampler2D texture1;
void main()
{
    vec4 texColor = texture(texture1, texCoord);
    if(texColor.a < 0.1)
      discard;
    FragColor = texColor;
}