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

uniform sampler2D texture1;
uniform vec3 lightColor;

uniform Material material;

void main(void)
{
    //ambient
    //vec3 ambientFinal = material.ambient * lightColor;
    //
    ////Diffuse
    //vec3 unitNormal = normalize(Normals);
    //vec3 unitToLight = normalize(toLightVec);
    //float dotvar = dot(unitNormal,unitToLight);
    //float brightness = max(dotvar,0.0);
    //vec3 diffuseFinal = lightColor * (brightness*material.diffuse);
    //
    ////specular
    //vec3 unitVectorToCamera = normalize(toCameraVector);
    //vec3 lightDirection = -unitToLight;
    //vec3 reflected = reflect(lightDirection, unitNormal);
    //
    //float specularFactor = dot(reflected, unitVectorToCamera);
    //specularFactor = max(specularFactor,0.0);
    //float specularDamped = pow(specularFactor,material.shininess);
    //vec3 specularfinal = lightColor * (specularDamped* material.specular);
    //
    //vec3 result = specularfinal+ambientFinal+diffuseFinal;

    if(material.shininess == 0.0)
    {
      FragColor = texture(texture1, texCoord);
	}
    else
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

    vec4 texColor = texture(texture1, texCoord)* vec4(result,1.0);
    FragColor = texColor;
    }
}