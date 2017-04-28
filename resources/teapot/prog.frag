#version 330 core

out vec4 color;
in vec3 norm, pos;
//in vec4 ShadowCoord;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Camera ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 cameraPosition;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Light ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 lightPosition, lightDirection;
uniform vec4 La, Ld, Ls;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teapot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec4 Ka, Kd, Ks;
uniform float Ns;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Type Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform int myTypeId;
uniform int lightId;

void main() {

    // | TYPE | Teapot | w_left | w_right | w_back | w_floor | w_ceil | w_front |
    // |------+--------+--------+---------+--------+---------+--------+---------|
    // | ID   |     10 |      0 |       1 |      2 |       3 |      4 |       5 |

    vec3 P, N, L, V, H;

    if (myTypeId == 4 && distance(vec2(0,0), pos.xz) < 1.0) {
	color = vec4(1.0, 1.0, 1.0, 1.0);
	return;
    }
    float dist = distance(pos, lightPosition);
    P = pos;
    N = normalize(norm);
    L = normalize(lightPosition - P);
    V = normalize(cameraPosition - P);
    H = normalize(L + V);
    vec4 diffuse = Ld* Kd * max(dot(N, L), 0.0) * 2.0 / dist;
    vec4 specular = Ls * Ks * pow(max(dot(H, N), 0.0), Ns) * 2.0 / dist;
    color = diffuse + specular;
    if (lightId == 0 || lightId == 1) color *= dist*dist;
}
