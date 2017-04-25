#version 330 core
out vec4 color;
in vec3 norm, pos;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Camera ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 cameraPosition;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Light ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 lightPosition, lightDirection;
uniform vec3 La, Ld, Ls;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teapot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 Ka, Kd, Ks;
uniform float Ns;

void main() {
    vec3 diffuse, specular, D, R;
    diffuse = Kd * Ld * max(0.0, dot(normalize(-vec3(lightDirection)),  normalize(norm)))*.00001;

    D = normalize(pos - lightPosition);
    R = normalize(D - norm * 2 * (dot(D, norm)));
    specular = Ks * Ls * pow(max(0.0, dot(R, -D)), Ns);

    color = vec4(Ka * La + diffuse + specular, 1.0);
}
