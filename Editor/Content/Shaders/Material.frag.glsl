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

void main()
{
    vec4 diffuseColor = texture(u_Material.diffuse, v_TexCoord);
    vec4 normalColor = texture(u_Material.normal, v_TexCoord);
    vec4 specularColor = texture(u_Material.specular, v_TexCoord);
    vec4 emissionColor = texture(u_Material.emission, v_TexCoord);

    vec3 normal = (any(greaterThan(normalColor.rgb, vec3(0.0))) || normalColor.a > 0.0) ? normalize(normalColor.rgb * 2.0 - 1.0) : normalize(v_Normal);

    // TODO: Implement lightning instead of using the Lambertian reflection model
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 1.0));
    float diffuseStrength = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseComponent = diffuseStrength * diffuseColor.rgb;

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularStrength = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.shininess);
    vec3 specularComponent = specularStrength * specularColor.rgb;

    vec3 finalColor = diffuseComponent + specularComponent + emissionColor.rgb;

    color = diffuseColor;
}
