#version 330 core

out vec3 norm, pos;
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Perspective ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uniform vec3 cameraPosition, cameraLookAt;
uniform mat4 projectionMtx, viewMtx, modelMtx, mvpMtx;


void main() {
    norm = vertexNormal;
    pos = vertexPosition;
    gl_Position = mvpMtx*vec4(vertexPosition, 1.0);
}
