#version 330 core

out vec4 norm, pos;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 vertexNormal;
//layout(location = 3) in vec3 vertexTangentX;
//layout(location = 4) in vec3 vertexTangentY;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Perspective ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 cameraPosition;
uniform vec3 cameraLookAt;

uniform mat4 projectionMtx;
uniform mat4 viewMtx;
uniform mat4 modelMtx;
uniform mat4 mvpMtx;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Light ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 lightPosition;
uniform vec3 lightDirection;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teapot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform mat4 rotationMtx;


void main() {
    norm = mvpMtx * vec4(vertexNormal, 0.0); //not complete
    pos = mvpMtx * vec4(vertexPosition, 1.0);


    gl_Position = mvpMtx*rotationMtx*vec4(vertexPosition, 1.0);
}
