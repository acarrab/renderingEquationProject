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

//shadow
//uniform sampler2DShadow shadowMap;
void main() {
    vec4 diffuse, specular;
    vec3 D, R;
    diffuse = Kd * Ld * max(0.0,
	dot(normalize(-vec3(lightDirection)),
	    normalize(norm)));

    D = normalize(pos - lightPosition);
    R = normalize(D - norm * 2 * (dot(D, norm)));
    specular = Ks * Ls * pow(max(0.0, dot(R, -D)), Ns);
    //get occlusion
    float visibility = 1.0;
/*    if ( texture(shadowMap, vec3(ShadowCoord.xy, ShadowCoord.z)/ShadowCoord.w) < ShadowCoord.z - .001) {
	visibility = .0;//for debugging it is 0
    }*/
    color = visibility * vec4(vec3(diffuse + specular), 1.0);
}
