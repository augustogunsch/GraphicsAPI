#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

out vec3 normal;
out vec2 textCoord;
out vec3 fragPosition;
out vec3 lightPos;

uniform vec3 lightPosition;

uniform mat4 modelM;
uniform mat4 viewM;
uniform mat4 projectionM;

void main() {
    gl_Position = projectionM * viewM * modelM * vec4(aPos, 1.0f);
    textCoord = aTextCoord;
    fragPosition = vec3(viewM * modelM * vec4(aPos, 1.0f));
    lightPos = vec3(viewM * vec4(lightPosition, 1.0f));
    
    // THE FOLLOWING PROCCESS OF CALCULATING NORMAL MATRIX SHOULD BE DONE IN CPU
    normal = mat3(transpose(inverse(viewM * modelM))) * aNormal;
}