#version 330 core

in vec2 textCoord;
in vec3 lighting;

out vec4 fragColor;

uniform sampler2D myTexture;
uniform vec3 objectColor;

void main() {
    vec3 result = lighting * vec3(texture(myTexture, textCoord));
    fragColor = vec4(result, 1.0f);
}