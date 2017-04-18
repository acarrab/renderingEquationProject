#version 330 core

out vec3 fragmentColor;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPosition, 1.0);
    fragmentColor = vertexColor;
}
