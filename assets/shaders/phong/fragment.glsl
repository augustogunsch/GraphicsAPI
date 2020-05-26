#version 330 core

struct Material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
    float emissionStrength;
};
uniform Material material;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform Light light;

in vec3 normal;
in vec2 textCoord;
in vec3 fragPosition;
in mat4 ViewM;

out vec4 fragColor;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightPosition = vec3(ViewM * vec4(light.position, 1.0f));
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    vec3 viewDirection = normalize(vec3(0, 0, 0) - fragPosition);
    
    // Ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.ambient, textCoord));
    // vec3 ambient = light.ambient * 0.2f * vec3(texture(material.ambient, textCoord));
    
    // Diffuse lighting
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, textCoord)));
    
    // Specular lighting
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, textCoord)));
    
    // Emission
    vec3 emission = vec3(texture(material.emission, textCoord)) * material.emissionStrength;
    
    
    vec3 result = (ambient + diffuse + specular + emission);
    fragColor = vec4(result, 1.0f);
}