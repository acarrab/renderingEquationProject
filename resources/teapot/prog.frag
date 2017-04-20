#version 330 core
out vec4 color;
in vec4 norm, pos;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Light ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 lightPosition;
uniform vec3 lightDirection;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teapot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec4 diffuseColor;
uniform vec4 specularColor;
uniform float shine;

void main() {
    vec3 P, N, L, V, H;
    float pi = 3.14159265;
    P = vec3(pos);
    N = normalize(vec3(norm));
    L = normalize(lightPosition - P);
    V = normalize(-P);
    H = normalize(L + V);

    vec4 diffuse = diffuseColor;
    vec4 specular = specularColor;

    diffuse *= max(dot(N, L), 0.0);
    specular *= ((shine + 2.0)/(8.0*pi))*pow(max(dot(H, N), 0.0), shine);
    color = (diffuse + specular);
}
