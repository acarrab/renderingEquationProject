#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 depthMVP;

void main() {
//    gl_Position = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = depthMVP * vec4(vertexPosition, 1.0);
}
