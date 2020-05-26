#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

out vec2 textCoord;
out vec3 lighting;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projectionM;

void main() {
    vec4 viewPos = viewM * modelM * vec4(aPos, 1.0f);
    gl_Position = projectionM * viewPos;
    textCoord = aTextCoord;
    
    vec3 lightPos = vec3(viewM * vec4(lightPosition, 1.0f));
    vec3 vertexPos = vec3(viewPos);
    
    // THE FOLLOWING PROCCESS OF CALCULATING NORMAL MATRIX SHOULD BE DONE IN CPU
    vec3 normal = mat3(transpose(inverse(viewM * modelM))) * aNormal;
    
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - vertexPos);
    vec3 viewDirection = normalize(vec3(0, 0, 0) - vertexPos);
    
    // Ambient lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    float diffuseStrength = 1.0f;
    float diff = max(dot(norm, lightDirection), 0.0f);
    vec3 diffuse = diffuseStrength * diff * lightColor;
    
    // Specular lighting
    float specularStrength = 0.5f;
    int shininess = 32;
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), shininess);
    vec3 specular = specularStrength * spec * lightColor;
    
    lighting = specular + diffuse + ambient;
}