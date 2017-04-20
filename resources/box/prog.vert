#version 330 core

out vec3 fragmentColor;

layout(location = 0) in vec3 vertexPosition;

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


void main() {
    gl_Position = mvpMtx * vec4(vertexPosition, 1.0);
    fragmentColor = vec3(1.0, 0.0, 0.0); //for testing
}
