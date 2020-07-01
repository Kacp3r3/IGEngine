

#version 440 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 toLightVec;
in vec3 toCameraVector;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;
uniform vec3 lightColor;

uniform Material material;

void main(void)
{
    // ambient
    vec3 ambient = lightColor * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(toLightVec);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(toCameraVector);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    //vec4 texColor = texture(texture_diffuse1, texCoord)* vec4(result,1.0);
    vec4 texColor = texture(texture_diffuse1, texCoord);
    //vec4 texColor = mix(vec4(1.0,0.,0.,1.0),texture(texture_diffuse1, texCoord),0.5);
    //vec4 texColor = mix(vec4(1.0,1.,1.0,1.0),texture(texture_diffuse1,texCoord),0.2)* vec4(result,1.0);
    //vec4 texColor = vec4(1.0,0.0,0.0,1.0) * vec4(result,1.0);
    FragColor = texColor;
}