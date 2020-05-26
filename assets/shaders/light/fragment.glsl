#version 330 core

in vec2 textCoord;
out vec4 fragColor;

uniform sampler2D myTexture;
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform Light light;

void main() {
    //fragColor = texture(myTexture, textCoord);
    fragColor = vec4(light.diffuse, 1.0f);
}