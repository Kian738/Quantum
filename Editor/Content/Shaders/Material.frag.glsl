#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

uniform vec3 v_ViewPosition;

struct Material
{
    sampler2D diffuse;
    sampler2D normal;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material u_Material;

vec3 viewDirection = normalize(v_ViewPosition - v_Position);

vec3 computeBlinnPhong(vec3 normal, vec3 lightDirection, vec3 viewDir, vec3 diffuseColor, vec3 specularColor, float shininess)
{
    float diffuseStrength = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseComponent = diffuseStrength * diffuseColor;

    vec3 halfwayDir = normalize(lightDirection + viewDir);
    float specularStrength = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specularComponent = specularStrength * specularColor;

    return diffuseComponent + specularComponent;
}

void main()
{
    vec4 diffuseColor = texture(u_Material.diffuse, v_TexCoord);
    vec4 normalColor = texture(u_Material.normal, v_TexCoord);
    vec4 specularColor = texture(u_Material.specular, v_TexCoord);
    vec4 emissionColor = pow(texture(u_Material.emission, v_TexCoord), vec4(2.2));

    vec3 normal = (any(greaterThan(normalColor.rgb, vec3(0.0))) || normalColor.a > 0.0)
        ? normalize(normalColor.rgb * 2.0 - 1.0)
        : normalize(v_Normal);

    vec3 lightDirection = normalize(vec3(1.0, 1.0, 1.0));

    vec3 finalColor = computeBlinnPhong(
        normal,
        lightDirection,
        viewDirection,
        diffuseColor.rgb,
        specularColor.rgb,
        u_Material.shininess
    ) + emissionColor.rgb;

    color = vec4(finalColor, diffuseColor.a);
}
