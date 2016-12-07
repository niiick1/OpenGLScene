#version 330

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texelIn;
layout(location = 2) in vec3 normal;

uniform mat4 proj, view, modelT, modelR;
uniform Light light;

out vec2 texel;
out vec3 lightDirection_world;
out vec3 normal_world;
out vec3 vertex_world;

void main() {
    mat4 model = (modelT * modelR);
    gl_Position = proj * view * model * vec4(vertex, 1.0);

    texel = texelIn;

    // lightDirection_world = vertex - light.position;
    // lightDirection_world = (model * vec4(vertex, 1.0)).xyz - light.position;
    lightDirection_world = (view * vec4(vertex, 1.0)).xyz - (view * vec4(light.position, 1.0)).xyz;
    // lightDirection_world = (view * (model * vec4(vertex, 1.0) - vec4(light.position, 1.0))).xyz;
    normal_world = (view * model * vec4(normal, 0.0)).xyz;
    vertex_world = (view * model * vec4(vertex, 1.0)).xyz;
}