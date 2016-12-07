#version 330 core

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float specularExponent;
};

in vec2 texel;

in vec3 lightDirection_world;
in vec3 normal_world;
in vec3 vertex_world;

uniform Light light;
uniform Material material;
uniform sampler2D texturePixels;
uniform vec3 eyeWorld;

out vec3 fragmentColor;

void main() {
    vec4 texelOut = texture(texturePixels, texel);

    // float lightDistance_view = length(lightDirection_view);
    // float attenuationFactor_view = 1 / (1.0 + 0.1 * lightDistance_view + 0.01 * pow(lightDistance_view, 2));
    // float attenuation_view = min(attenuationFactor_view, 1);
    // attenuation_view = 1;

    float lightDistance_world = length(lightDirection_world);
    float attenuationFactor_world = 1 / (1.0 + 0.05 * lightDistance_world + 0.005 * pow(lightDistance_world, 2));
    float attenuation_world = min(attenuationFactor_world, 1);
    // attenuation_world = 1;

    // vec3 normalV = normalize(normal_view);
    // vec3 vertex_viewNormalized = normalize(vertex_view);
    // vec3 lightDirection_viewNormalized = normalize(lightDirection_view);
    
    vec3 normalW = normalize(normal_world);
    vec3 lightDirection_worldNormalized = normalize(lightDirection_world);

    vec3 vertexToEye = normalize(eyeWorld - vertex_world);

    // Ambient
    vec3 ambientLight = light.ambient * material.ambientColor;

    // Diffuse
    float diffuseFactor_world = clamp(dot(-lightDirection_worldNormalized, normalW), 0, 1);
    vec3 diffuseLight = light.diffuse * material.diffuseColor * diffuseFactor_world;

    //Specular
    vec3 reflection = normalW * (1 - diffuseFactor_world) - lightDirection_worldNormalized;
    // vec3 reflection = reflect(-lightDirection_worldNormalized, normalW);
    float specularIntensity = clamp(dot(normalize(reflection), vertexToEye), 0, 1);
    // vec3 specularLight = vec3(0, 0, 0);
    // if (specularIntensity > 0)
    vec3 specularLight =  light.specular * material.specularColor * abs(pow(specularIntensity, material.specularExponent));

    // Final Lighting Intensity
    vec3 lighting_intensity = ambientLight + attenuation_world * (diffuseLight + specularLight);

    // Final color
    fragmentColor = texelOut.xyz * lighting_intensity;
    // fragmentColor = lighting_intensity;
}