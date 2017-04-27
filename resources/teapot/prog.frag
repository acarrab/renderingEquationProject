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
uniform bool lightId;

void main() {

    // | TYPE | Teapot | w_left | w_right | w_back | w_floor | w_ceil | w_front |
    // |------+--------+--------+---------+--------+---------+--------+---------|
    // | ID   |     10 |      0 |       1 |      2 |       3 |      4 |       5 |


    if (myTypeId == 4 && distance(vec2(0,0), pos.xz) < 1.0) {
	color = vec4(1.0, 1.0, 1.0, 1.0);
	return;
    }
    float dist = distance(pos, lightPosition);
    vec3 toLight = normalize(lightPosition - pos);
    vec3 toCam = normalize(cameraPosition - pos);

    //perfect reflectance vector
    vec3 refl = reflect(-toLight, norm);



    vec4 brdf = Ld * Kd * max(0.0,dot(toLight, norm)) * 2.0 / (dist);
    if (!lightId) brdf *= 0.0;
    vec4 diffuse = brdf;
    vec4 specular;

    float specularScalar = pow(max(0.0, dot(refl, toCam)), Ns);
    specular = Ks * Ls * specularScalar;

    specular = vec4(0,0,0,0);
    color = diffuse + specular;
    color.a = 1.0;
}
