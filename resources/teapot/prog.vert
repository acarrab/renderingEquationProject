#version 330 core

out vec3 norm, pos;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 vertexNormal;
//layout(location = 3) in vec3 vertexTangentX;
//layout(location = 4) in vec3 vertexTangentY;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Perspective ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 cameraPosition, cameraLookAt;

uniform mat4 projectionMtx, viewMtx, modelMtx, mvpMtx;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teapot ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform mat4 rotationMtx;


void main() {
    norm = vertexNormal;
    pos = vertexPosition;


    gl_Position = mvpMtx*rotationMtx*vec4(vertexPosition, 1.0);
}
